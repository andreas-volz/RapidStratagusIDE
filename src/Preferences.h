#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <string>

class Preferences
{
public: // Singleton
  static Preferences& getInstance();

private: // Singleton
  Preferences();

  Preferences(const Preferences&);

  virtual ~Preferences();

public:
  /**
   * The init() does really nothing. It's just there to satisfy the compiler from the initial caller if nothing else is done.
   */
  void init() {};

  std::string getStratagusGameDir();

  std::string getStratagusGameDataDir();

  std::string getRSIConfigDir();

  std::string getStratagusBinary();

private:

};

#endif // PREFERENCES_H
