#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// system
#include <iostream>

#include "Preferences.h"

using namespace std;

Preferences::Preferences()
{

};

Preferences::~Preferences()
{

}

Preferences &Preferences::getInstance()
{
  static Preferences instance;
  return instance;
}

std::string Preferences::getStratagusGameHomeDir()
{
  string dir("/home/andreas/.stratagus/sc");

  return dir;
}

std::string Preferences::getRSIConfigDir()
{
  string dir(getStratagusGameHomeDir() + "/" + "rsi_testscenario");

  return dir;
}
