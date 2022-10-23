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

  class ModelColumns : public Gtk::TreeModelColumnRecord
  {
  public:

    ModelColumns()
      { add(m_col_text); add(m_col_id); }

    Gtk::TreeModelColumn<Glib::ustring> m_col_text;
    Gtk::TreeModelColumn<int> m_col_id;
  };

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

  Gtk::ScrolledWindow scrollWindow;
  Gtk::TreeView mTreeView;
  Glib::RefPtr<Gtk::ListStore> mRefListStore;
  ModelColumns m_Columns;

  StratagusControl sControl;
};



#endif /* MAIN_H */
