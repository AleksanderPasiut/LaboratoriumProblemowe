#include "doubleVec.h"

namespace std
{
	#define OPERATOR_VV(TYPE) \
	vector<double>& operator TYPE (vector<double>& dis, const vector<double>& arg) \
	{\
		auto jt = arg.begin();\
		for (auto it = dis.begin(); it != dis.end(); ++it, ++jt)\
			*it TYPE *jt;\
		return dis;\
	}

	OPERATOR_VV(+=)
	OPERATOR_VV(-=)
	OPERATOR_VV(*=)
	OPERATOR_VV(/=)

	#define OPERATOR_VD(TYPE) \
	vector<double>& operator TYPE (vector<double>& dis, double arg) \
	{\
		for (auto it = dis.begin(); it != dis.end(); ++it)\
			*it TYPE arg;\
		return dis;\
	}

	OPERATOR_VD(+=)
	OPERATOR_VD(-=)
	OPERATOR_VD(*=)
	OPERATOR_VD(/=)
}
