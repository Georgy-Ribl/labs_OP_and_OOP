#ifndef ICOMMAND_H
#define ICOMMAND_H

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
    virtual void undo()    = 0;
};

#endif // ICOMMAND_H
