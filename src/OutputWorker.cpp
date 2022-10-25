/*
 * OutputWorker.cpp
 *
 *      Author: Andreas Volz
 */

#include "MainWindow.h"
#include "OutputWorker.h"

// system
#include <sstream>
#include <chrono>
#include <iostream>

using namespace std;

OutputWorker::OutputWorker() :
  m_Mutex(),
  m_shall_stop(false),
  m_has_stopped(false),
  m_message(),
  m_stdout(0),
  m_stderr(0)
{
}

OutputWorker::~OutputWorker()
{

}

void OutputWorker::setOutputSteams(int app_stdout, int app_stderr)
{
  m_stdout = app_stdout;
  m_stderr = app_stderr;
}

// Accesses to these data are synchronized by a mutex.
// Some microseconds can be saved by getting all data at once, instead of having
// separate get_fraction_done() and get_message() methods.
void OutputWorker::get_data(Glib::ustring* message) const
{
  std::lock_guard<std::mutex> lock(m_Mutex);

  if (message)
    *message = m_message;
}

void OutputWorker::stop_work()
{
  std::lock_guard<std::mutex> lock(m_Mutex);
  m_shall_stop = true;
}

bool OutputWorker::has_stopped() const
{
  std::lock_guard<std::mutex> lock(m_Mutex);
  return m_has_stopped;
}

void OutputWorker::do_work(MainWindow* caller)
{
  {

    std::lock_guard<std::mutex> lock(m_Mutex);

    m_has_stopped = false;
    m_message = "";
  } // The mutex is unlocked here by lock's destructor.

  // Simulate a long calculation.
  while(true)
  {
    //cout << "do_work..." << endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    {
      std::lock_guard<std::mutex> lock(m_Mutex);

      //cout << "m_stdout:"  << m_stdout << endl;
      //cout << "m_stderr:" << m_stderr << endl;
      string input_line;

      // TODO: also print stdout to the string, maybe both with other colors

      char buff[2000];
      int ssize = read(m_stderr,buff,2000);

      buff[ssize] = '\0';

      m_message = buff;

      //cout << "buff: "<< string(buff) << endl;
    }

    caller->notify();
  }

  {
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_shall_stop = false;
    m_has_stopped = true;
  }

  caller->notify();
}



