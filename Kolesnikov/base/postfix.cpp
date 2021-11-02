#include "postfix.h"
#include "eq_exception.h"
#include "stack.h"
#include <sstream>
#include <string>
#include <system_error>


template<class T>
void TPostfix::MakeOperation(const string& str, TStack<T>& stack,
 T first, T second, bool isdouble) const 
{
  if(isdouble){
    if (str == "+") { stack.Push(first + second); return; }
    if (str == "-") { stack.Push(first - second); return; }
    if (str == "/") { stack.Push(first / second); return; }
    if (str == "*") { stack.Push(first * second); return; }
    if (str == "^") { stack.Push(pow(first,second)); return; }
  }
  else {
    if (str == "cos") {stack.Push(cos(first)); return;}
    if (str == "sin") {stack.Push(sin(first)); return;}
    if (str == "tg") { stack.Push(tan(first)); return; }
    if (str == "ctg") { stack.Push(1/tan(first)); return; }
    if (str == "ln") { stack.Push(log(first)); return; }
    if (str == "exp") { stack.Push(exp(first)); return; }
    if (str == "sqrt") { stack.Push(sqrt(first)); return; }
    if (str == "mdl") {stack.Push(fabs(first)); return;}
  }
  return;
}

void TPostfix::ChangeExpression(const string& _infix)
{
  infix = _infix;
}

double TPostfix::ToDoubleNum(const string& str)
{
  double tmp = stod(str);
  return tmp;
}

bool TPostfix::IfDoubleNum(const string& str)
{
  try {
    double tmp = stod(str);
    return 1;
  }
  catch(invalid_argument& ex) {
    return 0;
  }
}

void TPostfix::InfixAnalyzer(const string& infix) const
{
  //Brackets
  int LBrackets = 0, RBrackets = 0;
	for (int i = 0; i < infix.size(); i++) {
		if (infix[i] == '(')
			LBrackets++;
		else if (infix[i] == ')')
			RBrackets++;
	}
	if (LBrackets != RBrackets) {
		throw EqExcepion(EqExcepion::incorrect_expression,
     "Differnt count of left and right brackets");
  }

  //Expression don`t start and end with operation (start: except + and -)
  //Make infix without ()
  string t_infix = "";
  for(char c : infix) {
    if(!(c== '(' || c== ')'))
      t_infix+=c;
  }
  if(t_infix[0] == '/' || t_infix[0] == '*' || t_infix[0] == '^')
    throw EqExcepion(EqExcepion::incorrect_expression,
    "Expression start with operator except + and -");
  if(IsInclude(op_data, string(1,t_infix[t_infix.size()-1])))
    throw EqExcepion(EqExcepion::incorrect_expression,
      "Expression end with operator");
  

  //Operators don`t go one to another
  bool op_pr = false;
  for(char c : infix) {
    if (IsInclude(op_data, string(1, c))) {
      if (!(c == '(' || c == ')')) {
        if (op_pr) {
          throw EqExcepion(EqExcepion::incorrect_expression,
            "After operator go operator");
        }
        op_pr = true;
      }
      else {op_pr = false; }
    }
    else { op_pr = false;}
  }

  // No open bracket before the operator
  bool open_bracket_pr = false;
  for(char c : infix) {
    if(c == '(') {
      open_bracket_pr = true;
    }
    else{
      open_bracket_pr = false;
      if((c != ')') && IsInclude(op_data, string(1,c))) {
        if(open_bracket_pr)
          throw EqExcepion(EqExcepion::incorrect_expression,
           "Operator after the open bracket");
      }
    }
  }
}

vector<string> TPostfix::Split(const string& str) const
{
  vector <string> tmp_vec;
  string tmp_str = "";
  bool isword = false;
  for (char c : str) {
    if (IsInclude(op_data, string(1, c))) {
      if (isword) {
        tmp_vec.push_back(tmp_str);
        tmp_str = "";
        isword = false;
      }
      tmp_vec.push_back(string(1, c));
      continue;
    }
    else if (c == ' ') {
      if (isword) {
        tmp_vec.push_back(tmp_str);
        tmp_str = "";
        isword = false;
      }
    }
    else {
      isword = true;
      tmp_str += c;
    }
  }
  if (isword) {
    tmp_vec.push_back(tmp_str);
  }
  return tmp_vec;
}

int TPostfix::Priority(const string& key)
{
  return op_data[key].priority;
}

int TPostfix::Operands(const string& key)
{
  return op_data[key].operands;
}

template<class T>
bool TPostfix::IsInclude(const map<string, T>& map, const string& key) const
{
  for(auto pair : map) {
    if(pair.first == key)
      return true;
  }
  return false;
}

string TPostfix::ToPostfix()
{
  postfix.clear();
  postfix_str = "";
  InfixAnalyzer(infix);
  vector <string> vec_infix = Split(infix);
  stacklen = vec_infix.size();
  TStack<string> OpStack(stacklen);
  for (int i = 0; i < stacklen; i++) {
    string tmp = vec_infix[i];
    if (IsInclude(op_data, tmp)) {
      if (tmp == "(" || tmp == ")") {
        if (tmp == "(") {
          OpStack.Push(tmp);
        }
        else {
          while (OpStack.Top() != "(")
          {
            postfix.push_back(OpStack.PopTop());
          }
          OpStack.PopTop();
        }
      }
      else {
        if (OpStack.IsEmpty())
          OpStack.Push(tmp);
        else {
          while (!OpStack.IsEmpty() && (op_data[OpStack.Top()].priority >= op_data[tmp].priority) &&
          (OpStack.Top() != "(") && (OpStack.Top() != ")")) {
            postfix.push_back(OpStack.PopTop());
          }
          OpStack.Push(tmp);
        }
      }
    }
    else {
      if(IfDoubleNum(string(1,tmp[0])))
        throw EqExcepion(EqExcepion::incorrect_expression,
        "Expression include variable started with number");
      postfix.push_back(tmp);
    }
  }
while (!OpStack.IsEmpty()) {
	postfix.push_back(OpStack.PopTop());
}
for (string str : postfix)
  postfix_str += str;
return postfix_str;
}

double TPostfix::Calculate()
{
  if(postfix_str == "")
    throw(EqExcepion(EqExcepion::calculate_empty_postfix,
    "Try to calculate empty postfix"));
  double first, second;
  double num;
  TStack<double> value(stacklen);
  vector<string> elements = postfix;
  map<string, double> operands;
  for (string element : elements){
    if(!IsInclude(op_data, element)){
      if(IsInclude(operands, element))
        value.Push(operands[element]);
      else if (IfDoubleNum(element)){
        num = ToDoubleNum(element);
        operands.emplace(element, num);
        value.Push(num);
      }
      else {
        double temp;
        cout << element << ":";
        cin >> temp;
        operands.emplace(element, temp);
        value.Push(temp);
        cout << "\n";
      }
    }
    else{
      if(op_data[element].operands == 2){            
        if(((element == "+")||(element == "-")) && (value.GetSize() == 1)){
          second = value.PopTop();                // -c +c support
          first = 0.0;
          MakeOperation(element, value, first, second, true);
        }
        else {
          second = value.PopTop();
          first = value.PopTop();
          if (element == "/" && second == 0.0)
              throw(EqExcepion(EqExcepion::zero_division, "Division by zero"));
          MakeOperation(element, value, first, second, true);
        }
      }
      else{
        first = value.PopTop();
        MakeOperation(element, value, first, 0.0, false);
      }
    }
  }
return value.PopTop();
}