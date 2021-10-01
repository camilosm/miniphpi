#include "BlocksCommand.h"

BlocksCommand::BlocksCommand(int line):Command(line){
}

BlocksCommand::~BlocksCommand(){
	Command* cmd;
	std::list<Command*>::iterator it, end;
	end = m_cmds.end();
	for(it = m_cmds.begin(); it!=end; it++){
		cmd = *it;
		delete cmd;
	}
}

void BlocksCommand::addCommand(Command* cmd){
	m_cmds.push_back(cmd);
}

void BlocksCommand::execute(){
	Command* cmd;
	std::list<Command*>::iterator it, end;
	end = m_cmds.end();
	for(it = m_cmds.begin(); it!=end; it++){
		cmd = *it;
		cmd->execute();
	}
}
