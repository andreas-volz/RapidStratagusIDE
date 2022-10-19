/*
 * Main.h
 *
  *      Author: Andreas Volz
 */

#ifndef MAIN_H
#define MAIN_H

// project
#include "StratagusControl.h"

// system
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>

class Main : public Gtk::Window
{
public:
  Main();
  virtual ~Main();

protected:
  //Signal handlers:
  void on_button1_clicked();
  void on_button2_clicked();
  void on_button3_clicked();

private:
  //Child widgets:
  Gtk::Button m_button1;
  Gtk::Button m_button2;
  Gtk::Button m_button3;
  Gtk::Box m_box1;

  StratagusControl sControl;
};



#endif /* MAIN_H */
