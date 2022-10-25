/*
 * OutputWorker.h
 *
 *      Author: Andreas Volz
 */

#ifndef OUTPUTWORKER_H
#define OUTPUTWORKER_H

#include <gtkmm.h>
#include <thread>
#include <mutex>

class MainWindow;

class OutputWorker
{
public:
  OutputWorker();
  virtual ~OutputWorker();

  // Thread function.
  void do_work(MainWindow* caller);

  void setOutputSteams(int app_stdout, int app_stderr);

  void get_data(Glib::ustring* message) const;
  void stop_work();
  bool has_stopped() const;

private:
  // Synchronizes access to member data.
  mutable std::mutex m_Mutex;

  // Data used by both GUI thread and worker thread.
  bool m_shall_stop;
  bool m_has_stopped;
  Glib::ustring m_message;

  int m_stdout;
  int m_stderr;
};

#endif /* OUTPUTWORKER_H */
