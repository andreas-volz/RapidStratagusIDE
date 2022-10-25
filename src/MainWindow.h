/*
 * Main.h
 *
  *      Author: Andreas Volz
 */

#ifndef MAIN_H
#define MAIN_H

// project
#include "StratagusControl.h"
#include "OutputWorker.h"

// system
#include <gtkmm.h>

class MainWindow : public Gtk::Window
{
public:
  MainWindow();
  virtual ~MainWindow();

  class ModelColumns : public Gtk::TreeModelColumnRecord
  {
  public:

    ModelColumns()
      { add(m_col_text); add(m_col_id); }

    Gtk::TreeModelColumn<Glib::ustring> m_col_text;
    Gtk::TreeModelColumn<int> m_col_id;
  };

  // Called from the worker thread.
  void notify();


protected:
  //Signal handlers:
  void on_button1_clicked();
  void on_button2_clicked();
  void on_button3_clicked();

private:
  // Dispatcher handler.
  void on_notification_from_worker_thread();

  void update_widgets();

  Gtk::Box m_box1;
  Gtk::Toolbar mToolbar;

  Gtk::ToolButton mToolButton1;
  Gtk::ToolButton mToolButton2;
  Gtk::ToolButton mToolButton3;

  Gtk::ScrolledWindow mScrollWindowLua;
  Gtk::TreeView mTreeView;
  Glib::RefPtr<Gtk::ListStore> mRefListStore;
  ModelColumns m_Columns;



  // Output Text View
  Gtk::ScrolledWindow mScrollWindowOutput;
  Gtk::TextView mTextViewOutput;
  Glib::RefPtr<Gtk::TextBuffer> mRefTextOutputBuffer;

  // Thread
  Glib::Dispatcher m_Dispatcher;
  OutputWorker m_Worker;

  StratagusControl sControl;

  std::thread* m_WorkerThread;
};



#endif /* MAIN_H */
