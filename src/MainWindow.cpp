// project
#include "Preferences.h"

// system
#include <iostream>
#include "MainWindow.h"

using namespace std;

int main(int argc, char *argv[])
{
  Preferences &preferences = Preferences::getInstance();
  preferences.init();

  auto app =
    Gtk::Application::create(argc, argv,
      "org.gtkmm.examples.base");

  MainWindow main;

  return app->run(main);
}


MainWindow::MainWindow() :
    m_box1(Gtk::Orientation::ORIENTATION_VERTICAL),
    m_Dispatcher(),
    m_Worker(),
    sControl(m_Worker),
    m_WorkerThread(nullptr)
{
  //Preferences &preferences = Preferences::getInstance();

  // Connect the handler to the dispatcher.
  m_Dispatcher.connect(sigc::mem_fun(*this, &MainWindow::on_notification_from_worker_thread));

  set_size_request(500, 500);
  set_title("RapidStratagusIDE");
  set_border_width(10);


  m_box1.pack_start(mToolbar, Gtk::PACK_SHRINK);


  m_box1.pack_start(mScrollWindowLua);

  mScrollWindowLua.add(mTreeView);

  add(m_box1);


  mToolButton1.set_label("Start");
  mToolButton1.set_icon_name("media-playback-start");
  mToolButton1.set_tooltip_text("Start");

  mToolButton2.set_label("Stop");
  mToolButton2.set_icon_name("system-shutdown");
  mToolButton2.set_tooltip_text("Stop");

  mToolButton3.set_label("Restart");
  mToolButton3.set_icon_name("system-reboot");
  mToolButton3.set_tooltip_text("Restart");

  mToolButton1.signal_clicked().connect( sigc::mem_fun(*this,
                  &MainWindow::on_button1_clicked) );

  mToolButton2.signal_clicked().connect( sigc::mem_fun(*this,
                &MainWindow::on_button2_clicked) );

  mToolButton3.signal_clicked().connect( sigc::mem_fun(*this,
                &MainWindow::on_button3_clicked) );

  mToolbar.add(mToolButton1);
  mToolbar.add(mToolButton2);
  mToolbar.add(mToolButton3);

  mRefListStore = Gtk::ListStore::create(m_Columns);

  mTreeView.set_model(mRefListStore);

  Gtk::TreeModel::Row row;

  std::vector<Glib::ustring> files = sControl.enumerate_files(sControl.getRSITestDir());

  int i = 0;
  for(auto file : files)
  {
    row = *(mRefListStore->append());
    row[m_Columns.m_col_id] = i;
    row[m_Columns.m_col_text] = file;
    i++;
  }

  mTreeView.append_column("Cases", m_Columns.m_col_text);

  // output test
  mTextViewOutput.set_editable(false);
  mScrollWindowOutput.add(mTextViewOutput);

  mScrollWindowOutput.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  mScrollWindowOutput.set_hexpand();
  mScrollWindowOutput.set_vexpand();

  m_box1.add(mScrollWindowOutput);

  mRefTextOutputBuffer = Gtk::TextBuffer::create();

  mTextViewOutput.set_buffer(mRefTextOutputBuffer);



  show_all_children();
}

void MainWindow::notify()
{
  m_Dispatcher.emit();
}

void MainWindow::on_notification_from_worker_thread()
{
  //cout << "on_notification_from_worker_thread()" << endl;

  if (m_WorkerThread && m_Worker.has_stopped())
  {
    // Work is done.
    if (m_WorkerThread->joinable())
      m_WorkerThread->join();
    delete m_WorkerThread;
    m_WorkerThread = nullptr;
    //update_start_stop_buttons();
  }
  update_widgets();
}


MainWindow::~MainWindow()
{

}

void MainWindow::on_button1_clicked()
{
  auto refTreeSelection = mTreeView.get_selection();
  auto iter = refTreeSelection->get_selected();
  if(iter) //If anything is selected
  {
    auto row = *iter;

    ModelColumns columns;
    Glib::ustring selectedString = row.get_value(columns.m_col_text);

    cout << "selected: " << selectedString << endl;

    sControl.writeRSIConfigContent(selectedString);
  }

  if (m_WorkerThread)
  {
    std::cout << "Can't start a worker thread while another one is running." << std::endl;
  }
  else
  {
    // Start a new worker thread.
    m_WorkerThread = new std::thread(
      [this]
      {
        m_Worker.do_work(this);
      });
  }

  sControl.start();
}

void MainWindow::on_button2_clicked()
{
  sControl.stop();
}

void MainWindow::on_button3_clicked()
{
  auto refTreeSelection = mTreeView.get_selection();
  auto iter = refTreeSelection->get_selected();
  if(iter) //If anything is selected
  {
    auto row = *iter;

    ModelColumns columns;
    Glib::ustring selectedString = row.get_value(columns.m_col_text);

    cout << "selected: " << selectedString << endl;

    sControl.writeRSIConfigContent(selectedString);
  }

  sControl.restart();
}

void MainWindow::update_widgets()
{
  Glib::ustring message_from_worker_thread;
  m_Worker.get_data(&message_from_worker_thread);


  Gtk::TextBuffer::iterator iter_end;
  iter_end = mRefTextOutputBuffer->get_iter_at_offset(mRefTextOutputBuffer->get_char_count());
  mRefTextOutputBuffer->insert(iter_end, message_from_worker_thread);

  // move cursor to the end after insert
  auto it = mRefTextOutputBuffer->get_iter_at_line(mRefTextOutputBuffer->get_line_count());

  mTextViewOutput.scroll_to(it);


}
