#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <map>

#include "SetExpr.h"

class Variable: public SetExpr{
	public:
		virtual ~Variable();

		static Variable* instance(const std::string& name);
		const std::string& getName() { return m_name; }
		virtual Type* expr();
		void setExpr(Type* value) {m_value = value;}

	private:
		Variable(const std::string& name);

		static std::map<std::string, Variable*> m_variables;
		const std::string m_name;
		Type* m_value;
};

#endif
