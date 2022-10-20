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

  set_title("RapidStratagusIDE");
  set_border_width(10);

  m_box1.pack_start(mToolbar);

  add(m_box1);

  mToolButton1.set_label("Start");
  mToolButton1.set_tooltip_text("Start");

  mToolButton2.set_label("Stop");
  mToolButton2.set_tooltip_text("Stop");

  mToolButton3.set_label("Restart");
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
