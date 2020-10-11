#include "BlocksCommand.h"

BlocksCommand::BlocksCommand(int line):Command(line){
}

BlocksCommand::~BlocksCommand(){
}

void BlocksCommand::addCommand(Command* cmd){
	m_cmds.push_back(cmd);
}

void BlocksCommand::execute(){
	Command* m;
	std::list<Command*>::iterator it, ed;
	ed = m_cmds.end();
	for(it = m_cmds.begin(); it!=ed; it++){
		m = *it;
		m->execute();
	}
}
