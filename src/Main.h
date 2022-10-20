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
#include <gtkmm.h>

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
  Gtk::Box m_box1;
  Gtk::Toolbar mToolbar;

  Gtk::ToolButton mToolButton1;
  Gtk::ToolButton mToolButton2;
  Gtk::ToolButton mToolButton3;


  StratagusControl sControl;
};



#endif /* MAIN_H */
