// project
#include "Main.h"
#include "Preferences.h"

// system
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  Preferences &preferences = Preferences::getInstance();
  preferences.init();

  auto app =
    Gtk::Application::create(argc, argv,
      "org.gtkmm.examples.base");

  Main main;

  return app->run(main);
}


Main::Main() :
    m_box1(Gtk::Orientation::ORIENTATION_VERTICAL)
{
  //Preferences &preferences = Preferences::getInstance();

  set_size_request(250, 500);
  set_title("RapidStratagusIDE");
  set_border_width(10);


  m_box1.pack_start(mToolbar, Gtk::PACK_SHRINK);


  m_box1.pack_start(scrollWindow);

  scrollWindow.add(mTreeView);

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
                  &Main::on_button1_clicked) );

  mToolButton2.signal_clicked().connect( sigc::mem_fun(*this,
                &Main::on_button2_clicked) );

  mToolButton3.signal_clicked().connect( sigc::mem_fun(*this,
                &Main::on_button3_clicked) );

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

  show_all_children();
}

Main::~Main()
{

}

void Main::on_button1_clicked()
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

  sControl.start();
}

void Main::on_button2_clicked()
{
  sControl.stop();
}

void Main::on_button3_clicked()
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
