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


Main::Main()
{
  //Preferences &preferences = Preferences::getInstance();

  m_button1.add_label("Start stratagus");
  m_button2.add_label("Stop stratagus");
  m_button3.add_label("Restart stratagus");

  set_title("RapidStratagusIDE");
  set_border_width(10);

  m_button1.signal_clicked().connect( sigc::mem_fun(*this,
                &Main::on_button1_clicked) );

  m_button2.signal_clicked().connect( sigc::mem_fun(*this,
                &Main::on_button2_clicked) );

  m_button3.signal_clicked().connect( sigc::mem_fun(*this,
                &Main::on_button3_clicked) );

  m_box1.pack_start(m_button1);
  m_box1.pack_start(m_button2);
  m_box1.pack_start(m_button3);

  add(m_box1);

  show_all_children();
}

Main::~Main()
{

}

void Main::on_button1_clicked()
{
  sControl.start();
}

void Main::on_button2_clicked()
{
  sControl.stop();
}

void Main::on_button3_clicked()
{
  sControl.restart();
}
