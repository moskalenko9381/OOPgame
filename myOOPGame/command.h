#ifndef COMMAND_H
#define COMMAND_H

class Command {
 public:
  virtual ~Command(){}
  virtual void execute() const = 0;
};

#endif // COMMAND_H

