#pragma once

class FunctionSignature
{
public:
	// getter method
	unsigned getArgc() const { return m_argc; }
	const MetaData *getRet() const { return m_ret; }
	const MetaData *getArgs(unsigned i) const { return m_args[i]; }
	const MetaData *getContext() const { return m_context; }

	FunctionSignature(void) : m_argc(0), m_args(NULL), m_ret(NULL), m_context(NULL) {}
	FunctionSignature(const FunctionSignature& fs) :m_args(fs.m_args), m_argc(fs.m_argc), m_ret(fs.m_ret), m_context(fs.m_context) {}
	FunctionSignature& operator = (const FunctionSignature& fs) {
		m_args = fs.m_args;
		m_argc = fs.m_argc;
		m_ret = fs.m_ret;
		m_context = fs.m_context;
	}

	// static method with return values
	template<typename R>
	FunctionSignature(R(*fn)(void)) :m_argc(0), m_ret(META_TYPE(R)), m_context(NULL), m_args(NULL) {}

	template<typename R, typename arg1>
	FunctionSignature(R(*fn)(arg1)) : m_argc(1), m_ret(META_TYPE(R)), m_context(NULL) {
		static const MetaData* args[] = {
			META_TYPE(arg1)
		};
		m_args = args;
	}
	template<typename R, typename arg1, typename arg2>
	FunctionSignature(R(*fn)(arg1, arg2)) :m_argc(2), m_ret(META_TYPE(R)), m_context(NULL) {
		static const MetaData* args[] = {
			META_TYPE(arg1),
			META_TYPE(arg2)
		};
		m_args = args;
	}
	template<typename R, typename arg1, typename arg2, typename arg3>
	FunctionSignature(R(*fn)(arg1, arg2, arg3)) :m_argc(3), m_ret(META_TYPE(R)), m_context(NULL) {
		static const MetaData* args[] = {
			META_TYPE(arg1),
			META_TYPE(arg2),
			META_TYPE(arg3)
		};
		m_args = args;
	}
	template<typename R, typename arg1, typename arg2, typename arg3, typename arg4>
	FunctionSignature(R(*fn)(arg1, arg2, arg3, arg4)) :m_argc(4), m_ret(META_TYPE(R)), m_context(NULL) {
		static const MetaData* args[] = {
			META_TYPE(arg1),
			META_TYPE(arg2),
			META_TYPE(arg3),
			META_TYPE(arg4)
		};
		m_args = args;
	}
	// static method with non-return
	template<>
	FunctionSignature(void(*fn)(void)) :m_argc(0), m_ret(NULL), m_context(NULL), m_args(NULL) {}
	template<typename arg1>
	FunctionSignature(void(*fn)(arg1)) : m_argc(1), m_ret(NULL), m_context(NULL) {
		static const MetaData* args[] = {
			META_TYPE(arg1)
		};
		m_args = args;
	}
	template<typename arg1, typename arg2>
	FunctionSignature(void(*fn)(arg1, arg2)) :m_argc(2), m_ret(NULL), m_context(NULL) {
		static const MetaData* args[] = {
			META_TYPE(arg1),
			META_TYPE(arg2)
		};
		m_args = args;
	}
	template<typename arg1, typename arg2, typename arg3>
	FunctionSignature(void(*fn)(arg1, arg2, arg3)) :m_argc(3), m_ret(NULL), m_context(NULL) {
		static const MetaData* args[] = {
			META_TYPE(arg1),
			META_TYPE(arg2),
			META_TYPE(arg3)
		};
		m_args = args;
	}
	template<typename arg1, typename arg2, typename arg3, typename arg4>
	FunctionSignature(void(*fn)(arg1, arg2, arg3, arg4)) :m_argc(4), m_ret(NULL), m_context(NULL) {
		static const MetaData* args[] = {
			META_TYPE(arg1),
			META_TYPE(arg2),
			META_TYPE(arg3),
			META_TYPE(arg4)
		};
		m_args = args;
	}
	// member method with return values
	template<typename R, typename C>
	FunctionSignature(R(C::*fn)(void)) :m_argc(0), m_ret(META_TYPE(R)), m_context(META_TYPE(C)), m_args(NULL) {}
	template<typename R, typename C, typename arg1>
	FunctionSignature(R(C::*fn)(arg1)) : m_argc(1), m_ret(META_TYPE(R)), m_context(META_TYPE(C)) {
		static const MetaData* args[] = {
			META_TYPE(arg1)
		};
		m_args = args;
	}
	template<typename R, typename C, typename arg1, typename arg2>
	FunctionSignature(R(C::*fn)(arg1, arg2)) :m_argc(2), m_ret(META_TYPE(R)), m_context(META_TYPE(C)) {
		static const MetaData* args[] = {
			META_TYPE(arg1),
			META_TYPE(arg2)
		};
		m_args = args;
	}
	template<typename R, typename C, typename arg1, typename arg2, typename arg3>
	FunctionSignature(R(C::*fn)(arg1, arg2, arg3)) :m_argc(3), m_ret(META_TYPE(R)), m_context(META_TYPE(C)) {
		static const MetaData* args[] = {
			META_TYPE(arg1),
			META_TYPE(arg2),
			META_TYPE(arg3)
		};
		m_args = args;
	}
	template<typename R, typename C, typename arg1, typename arg2, typename arg3, typename arg4>
	FunctionSignature(R(C::*fn)(arg1, arg2, arg3, arg4)) :m_argc(4), m_ret(META_TYPE(R)), m_context(META_TYPE(C)) {
		static const MetaData* args[] = {
			META_TYPE(arg1),
			META_TYPE(arg2),
			META_TYPE(arg3),
			META_TYPE(arg4)
		};
		m_args = args;
	}
	// member method with non-return
	template<typename C>
	FunctionSignature(void (C::*fn)(void)) :m_argc(0), m_ret(NULL), m_context(META_TYPE(C)), m_args(NULL) {}
	template<typename C, typename arg1>
	FunctionSignature(void (C::*fn)(arg1)) : m_argc(1), m_ret(NULL), m_context(META_TYPE(C)) {
		static const MetaData* args[] = {
			META_TYPE(arg1)
		};
		m_args = args;
	}
	template<typename C, typename arg1, typename arg2>
	FunctionSignature(void (C::*fn)(arg1, arg2)) :m_argc(2), m_ret(NULL), m_context(META_TYPE(C)) {
		static const MetaData* args[] = {
			META_TYPE(arg1),
			META_TYPE(arg2)
		};
		m_args = args;
	}
	template<typename C, typename arg1, typename arg2, typename arg3>
	FunctionSignature(void (C::*fn)(arg1, arg2, arg3)) :m_argc(3), m_ret(NULL), m_context(META_TYPE(C)) {
		static const MetaData* args[] = {
			META_TYPE(arg1),
			META_TYPE(arg2),
			META_TYPE(arg3)
		};
		m_args = args;
	}
	template<typename C, typename arg1, typename arg2, typename arg3, typename arg4>
	FunctionSignature(void (C::*fn)(arg1, arg2, arg3, arg4)) :m_argc(4), m_ret(NULL), m_context(META_TYPE(C)) {
		static const MetaData* args[] = {
			META_TYPE(arg1),
			META_TYPE(arg2),
			META_TYPE(arg3),
			META_TYPE(arg4)
		};
		m_args = args;
	}
	// member method with return values and const
	template<typename R, typename C>
	FunctionSignature(R(C::*fn)(void) const) :m_argc(0), m_ret(META_TYPE(R)), m_context(META_TYPE(C)), m_args(NULL) {}
	template<typename R, typename C, typename arg1>
	FunctionSignature(R(C::*fn)(arg1) const) : m_argc(1), m_ret(META_TYPE(R)), m_context(META_TYPE(C)) {
		static const MetaData* args[] = {
			META_TYPE(arg1)
		};
		m_args = args;
	}
	template<typename R, typename C, typename arg1, typename arg2>
	FunctionSignature(R(C::*fn)(arg1, arg2) const) :m_argc(2), m_ret(META_TYPE(R)), m_context(META_TYPE(C)) {
		static const MetaData* args[] = {
			META_TYPE(arg1),
			META_TYPE(arg2)
		};
		m_args = args;
	}
	template<typename R, typename C, typename arg1, typename arg2, typename arg3>
	FunctionSignature(R(C::*fn)(arg1, arg2, arg3) const) :m_argc(3), m_ret(META_TYPE(R)), m_context(META_TYPE(C)) {
		static const MetaData* args[] = {
			META_TYPE(arg1),
			META_TYPE(arg2),
			META_TYPE(arg3)
		};
		m_args = args;
	}
	template<typename R, typename C, typename arg1, typename arg2, typename arg3, typename arg4>
	FunctionSignature(R(C::*fn)(arg1, arg2, arg3, arg4) const) :m_argc(4), m_ret(META_TYPE(R)), m_context(META_TYPE(C)) {
		static const MetaData* args[] = {
			META_TYPE(arg1),
			META_TYPE(arg2),
			META_TYPE(arg3),
			META_TYPE(arg4)
		};
		m_args = args;
	}
	// member method with const
	template<typename C>
	FunctionSignature(void (C::*fn)(void) const) :m_argc(0), m_ret(NULL), m_context(META_TYPE(C)), m_args(NULL) {}
	template<typename C, typename arg1>
	FunctionSignature(void (C::*fn)(arg1) const) : m_argc(1), m_ret(NULL), m_context(META_TYPE(C)) {
		static const MetaData* args[] = {
			META_TYPE(arg1)
		};
		m_args = args;
	}
	template<typename C, typename arg1, typename arg2>
	FunctionSignature(void (C::*fn)(arg1, arg2) const) :m_argc(2), m_ret(NULL), m_context(META_TYPE(C)) {
		static const MetaData* args[] = {
			META_TYPE(arg1),
			META_TYPE(arg2)
		};
		m_args = args;
	}
	template<typename C, typename arg1, typename arg2, typename arg3>
	FunctionSignature(void (C::*fn)(arg1, arg2, arg3) const) :m_argc(3), m_ret(NULL), m_context(META_TYPE(C)) {
		static const MetaData* args[] = {
			META_TYPE(arg1),
			META_TYPE(arg2),
			META_TYPE(arg3)
		};
		m_args = args;
	}
	template<typename C, typename arg1, typename arg2, typename arg3, typename arg4>
	FunctionSignature(void (C::*fn)(arg1, arg2, arg3, arg4) const) :m_argc(4), m_ret(NULL), m_context(META_TYPE(C)) {
		static const MetaData* args[] = {
			META_TYPE(arg1),
			META_TYPE(arg2),
			META_TYPE(arg3),
			META_TYPE(arg4)
		};
		m_args = args;
	}
private:
	const MetaData *m_ret;
	const MetaData **m_args;
	const MetaData *m_context;
	unsigned m_argc;
};

class Function
{
public:
	// default constructor
	Function(void) :m_fsig(), m_callHelper(NULL) {}
	// copy constructor
	Function(const Function& rhs) :m_fsig(rhs.m_fsig), m_callHelper(rhs.m_callHelper) {}
	// allocate operator
	Function& operator = (const Function& rhs) { m_fsig = rhs.m_fsig; m_callHelper = rhs.m_callHelper; return *this; }
	const FunctionSignature *Signature() const { return &m_fsig; }

	// static method with return values
	template<typename R>
	Function(R(*fn)(void), void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename R, typename arg1>
	Function(R(*fn)(arg1), void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename R, typename arg1, typename arg2>
	Function(R(*fn)(arg1, arg2), void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename R, typename arg1, typename arg2, typename arg3>
	Function(R(*fn)(arg1, arg2, arg3), void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename R, typename arg1, typename arg2, typename arg3, typename arg4>
	Function(R(*fn)(arg1, arg2, arg3, arg4), void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	// static method with non-return
	template<>
	Function(void(*fn)(void), void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename arg1>
	Function(void(*fn)(arg1), void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename arg1, typename arg2>
	Function(void(*fn)(arg1, arg2), void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename arg1, typename arg2, typename arg3>
	Function(void(*fn)(arg1, arg2, arg3), void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename arg1, typename arg2, typename arg3, typename arg4>
	Function(void(*fn)(arg1, arg2, arg3, arg4), void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}

	// member method with return values
	template<typename R, typename C>
	Function(R(C::*fn)(void), void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename R, typename C, typename arg1>
	Function(R(C::*fn)(arg1), void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename R, typename C, typename arg1, typename arg2>
	Function(R(C::*fn)(arg1, arg2), void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename R, typename C, typename arg1, typename arg2, typename arg3>
	Function(R(C::*fn)(arg1, arg2, arg3), void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename R, typename C, typename arg1, typename arg2, typename arg3, typename arg4>
	Function(R(C::*fn)(arg1, arg2, arg3, arg4), void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	// member method with non-return
	template<typename C>
	Function(void (C::*fn)(void), void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename C, typename arg1>
	Function(void (C::*fn)(arg1), void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename C, typename arg1, typename arg2>
	Function(void (C::*fn)(arg1, arg2), void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename C, typename arg1, typename arg2, typename arg3>
	Function(void (C::*fn)(arg1, arg2, arg3), void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename C, typename arg1, typename arg2, typename arg3, typename arg4>
	Function(void (C::*fn)(arg1, arg2, arg3, arg4), void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}

	// member method with return values and const
	template<typename R, typename C>
	Function(R(C::*fn)(void) const, void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename R, typename C, typename arg1>
	Function(R(C::*fn)(arg1) const, void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename R, typename C, typename arg1, typename arg2>
	Function(R(C::*fn)(arg1, arg2) const, void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename R, typename C, typename arg1, typename arg2, typename arg3>
	Function(R(C::*fn)(arg1, arg2, arg3) const, void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename R, typename C, typename arg1, typename arg2, typename arg3, typename arg4>
	Function(R(C::*fn)(arg1, arg2, arg3, arg4) const, void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	// member method with const
	template<typename C>
	Function(void (C::*fn)(void) const, void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename C, typename arg1>
	Function(void (C::*fn)(arg1) const, void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename C, typename arg1, typename arg2>
	Function(void (C::*fn)(arg1, arg2) const, void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename C, typename arg1, typename arg2, typename arg3>
	Function(void (C::*fn)(arg1, arg2, arg3) const, void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}
	template<typename C, typename arg1, typename arg2, typename arg3, typename arg4>
	Function(void (C::*fn)(arg1, arg2, arg3, arg4) const, void(*helper)(Variable *, void *, Variable *, unsigned)) : m_fsig(fn), m_callHelper(helper) {}

	// operator ()
	void operator( )(Variable& ret, Variable *args, unsigned argCount) const {
		m_callHelper(&ret, m_context.Data(), args, argCount);
	}
	void operator( )(Variable& ret, Variable *args, unsigned argCount) {
		m_callHelper(&ret, m_context.Data(), args, argCount);
	}

	void operator( )(Variable& ret) const {
		m_callHelper(&ret, m_context.Data(), NULL, 0);
	}
	template <typename Arg1>
	void operator( )(Variable& ret, Arg1 arg1) const {
		assert(m_fsig.getArgc() == 1);
		assert(m_fsig.getArgs(0) == META_TYPE(Arg1));

		Variable argStack[1];

		new (argStack) Variable(arg1);

		m_callHelper(&ret, m_context.Data(), argStack, m_fsig.getArgc());
	}
	template <typename Arg1, typename Arg2>
	void operator( )(Variable& ret, Arg1 arg1, Arg2 arg2) const {
		assert(m_fsig.getArgc() == 2);
		assert(m_fsig.getArgs(0) == META_TYPE(Arg1));
		assert(m_fsig.getArgs(1) == META_TYPE(Arg2));

		Variable argStack[2];

		new (argStack) Variable(arg1);
		new (argStack + 1) Variable(arg2);

		m_callHelper(&ret, m_context.Data(), argStack, m_fsig.getArgc());
	}
	template <typename Arg1, typename Arg2, typename Arg3>
	void operator( )(Variable& ret, Arg1 arg1, Arg2 arg2, Arg3 arg3) const {
		assert(m_fsig.getArgc() == 3);
		assert(m_fsig.getArgs(0) == META_TYPE(Arg1));
		assert(m_fsig.getArgs(1) == META_TYPE(Arg2));
		assert(m_fsig.getArgs(2) == META_TYPE(Arg3));

		Variable argStack[3];

		new (argStack) Variable(arg1);
		new (argStack + 1) Variable(arg2);
		new (argStack + 2) Variable(arg3);

		m_callHelper(&ret, m_context.Data(), argStack, m_fsig.getArgc());
	}
	template <typename Arg1, typename Arg2, typename Arg3, typename Arg4>
	void operator( )(Variable& ret, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4) const {
		assert(m_fsig.getArgc() == 4);
		assert(m_fsig.getArgs(0) == META_TYPE(Arg1));
		assert(m_fsig.getArgs(1) == META_TYPE(Arg2));
		assert(m_fsig.getArgs(2) == META_TYPE(Arg3));
		assert(m_fsig.getArgs(3) == META_TYPE(Arg4));

		Variable argStack[4];

		new (argStack) Variable(arg1);
		new (argStack + 1) Variable(arg2);
		new (argStack + 2) Variable(arg3);
		new (argStack + 3) Variable(arg4);

		m_callHelper(&ret, m_context.Data(), argStack, m_fsig.getArgc());
	}

	void operator( )(void) const {
		m_callHelper(NULL, m_context.Data(), NULL, 0);
	}
	template <typename Arg1>
	void operator( )(Arg1 arg1) const {
		assert(m_fsig.getArgc() == 1);
		assert(m_fsig.getArgs(0) == META_TYPE(Arg1));

		Variable argStack[1];

		new (argStack) Variable(arg1);

		m_callHelper(NULL, m_context.Data(), argStack, m_fsig.getArgc());
	}
	template <typename Arg1, typename Arg2>
	void operator( )(Arg1 arg1, Arg2 arg2) const {
		assert(m_fsig.getArgc() == 2);
		assert(m_fsig.getArgs(0) == META_TYPE(Arg1));
		assert(m_fsig.getArgs(1) == META_TYPE(Arg2));

		Variable argStack[2];

		new (argStack) Variable(arg1);
		new (argStack + 1) Variable(arg2);

		m_callHelper(NULL, m_context.Data(), argStack, m_fsig.getArgc());
	}
	template <typename Arg1, typename Arg2, typename Arg3>
	void operator( )(Arg1 arg1, Arg2 arg2, Arg3 arg3) const {
		assert(m_fsig.getArgc() == 3);
		assert(m_fsig.getArgs(0) == META_TYPE(Arg1));
		assert(m_fsig.getArgs(1) == META_TYPE(Arg2));
		assert(m_fsig.getArgs(2) == META_TYPE(Arg3));

		Variable argStack[3];

		new (argStack) Variable(arg1);
		new (argStack + 1) Variable(arg2);
		new (argStack + 1) Variable(arg3);

		m_callHelper(NULL, m_context.Data(), argStack, m_fsig.getArgc());
	}
	template <typename Arg1, typename Arg2, typename Arg3, typename Arg4>
	void operator( )(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4) const {
		assert(m_fsig.getArgc() == 4);
		assert(m_fsig.getArgs(0) == META_TYPE(Arg1));
		assert(m_fsig.getArgs(1) == META_TYPE(Arg2));
		assert(m_fsig.getArgs(2) == META_TYPE(Arg3));
		assert(m_fsig.getArgs(3) == META_TYPE(Arg4));

		Variable argStack[4];

		new (argStack) Variable(arg1);
		new (argStack + 1) Variable(arg2);
		new (argStack + 2) Variable(arg3);
		new (argStack + 3) Variable(arg4);

		m_callHelper(NULL, m_context.Data(), argStack, m_fsig.getArgc());
	}

private:
	Variable m_context;
	FunctionSignature m_fsig;
	void(*m_callHelper)(Variable *, void *, Variable *, unsigned);
};

// Static functions with return value
template <typename FunctionType, FunctionType FunctionPtr, typename R>
void Call(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 0);

	ret->GetValue<R>() = (*FunctionPtr)();
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename Arg1>
void Call(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 1);

	ret->GetValue<R>() = (*FunctionPtr)(
		args[0].GetValue<Arg1>()
		);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename Arg1, typename Arg2>
void Call(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 2);

	ret->GetValue<R>() = (*FunctionPtr)(
		args[0].GetValue<Arg1>(),
		args[1].GetValue<Arg2>()
		);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename Arg1, typename Arg2, typename Arg3>
void Call(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 3);

	ret->GetValue<R>() = (*FunctionPtr)(
		args[0].GetValue<Arg1>(),
		args[1].GetValue<Arg2>(),
		args[2].GetValue<Arg3>()
		);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
void Call(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 4);

	ret->GetValue<R>() = (*FunctionPtr)(
		args[0].GetValue<Arg1>(),
		args[1].GetValue<Arg2>(),
		args[2].GetValue<Arg3>(),
		args[3].GetValue<Arg4>()
		);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
void Call(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 5);

	ret->GetValue<R>() = (*FunctionPtr)(
		args[0].GetValue<Arg1>(),
		args[1].GetValue<Arg2>(),
		args[2].GetValue<Arg3>(),
		args[3].GetValue<Arg4>(),
		args[4].GetValue<Arg5>()
		);
}

// Call static function without return value
template <typename FunctionType, FunctionType FunctionPtr>
void CallVoid(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 0);

	(*FunctionPtr)();
}

template <typename FunctionType, FunctionType FunctionPtr, typename Arg1>
void CallVoid(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 1);

	(*FunctionPtr)(
		args[0].GetValue<Arg1>()
		);
}

template <typename FunctionType, FunctionType FunctionPtr, typename Arg1, typename Arg2>
void CallVoid(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 2);

	(*FunctionPtr)(
		args[0].GetValue<Arg1>(),
		args[1].GetValue<Arg2>()
		);
}

template <typename FunctionType, FunctionType FunctionPtr, typename Arg1, typename Arg2, typename Arg3>
void CallVoid(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 3);

	(*FunctionPtr)(
		args[0].GetValue<Arg1>(),
		args[1].GetValue<Arg2>(),
		args[2].GetValue<Arg3>()
		);
}

template <typename FunctionType, FunctionType FunctionPtr, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
void CallVoid(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 4);

	(*FunctionPtr)(
		args[0].GetValue<Arg1>(),
		args[1].GetValue<Arg2>(),
		args[2].GetValue<Arg3>(),
		args[3].GetValue<Arg4>()
		);
}

template <typename FunctionType, FunctionType FunctionPtr, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
void CallVoid(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 5);

	(*FunctionPtr)(
		args[0].GetValue<Arg1>(),
		args[1].GetValue<Arg2>(),
		args[2].GetValue<Arg3>(),
		args[3].GetValue<Arg4>(),
		args[4].GetValue<Arg5>()
		);
}

// Methods with return value
template <typename FunctionType, FunctionType FunctionPtr, typename R, typename C>
void CallMethod(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 0);
	ret->GetValue<R>() = (((C *)context)->*FunctionPtr)();
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename C, typename Arg1>
void CallMethod(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 1);
	ret->GetValue<R>() = (((C *)context)->*FunctionPtr)(
		args[0].GetValue<Arg1>()
		);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename C, typename Arg1, typename Arg2>
void CallMethod(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 2);
	ret->GetValue<R>() = (((C *)context)->*FunctionPtr)(
		args[0].GetValue<Arg1>(),
		args[1].GetValue<Arg2>()
		);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename C, typename Arg1, typename Arg2, typename Arg3>
void CallMethod(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 3);
	ret->GetValue<R>() = (((C *)context)->*FunctionPtr)(
		args[0].GetValue<Arg1>(),
		args[1].GetValue<Arg2>(),
		args[2].GetValue<Arg3>()
		);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename C, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
void CallMethod(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 4);
	ret->GetValue<R>() = (((C *)context)->*FunctionPtr)(
		args[0].GetValue<Arg1>(),
		args[1].GetValue<Arg2>(),
		args[2].GetValue<Arg3>(),
		args[3].GetValue<Arg4>()
		);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename C, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
void CallMethod(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 5);
	ret->GetValue<R>() = (((C *)context)->*FunctionPtr)(
		args[0].GetValue<Arg1>(),
		args[1].GetValue<Arg2>(),
		args[2].GetValue<Arg3>(),
		args[3].GetValue<Arg4>(),
		args[4].GetValue<Arg5>()
		);
}

// Methods without return value
template <typename FunctionType, FunctionType FunctionPtr, typename C>
void CallMethodVoid(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 0);
	(((C *)context)->*FunctionPtr)();
}

template <typename FunctionType, FunctionType FunctionPtr, typename C, typename Arg1>
void CallMethodVoid(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 1);
	(((C *)context)->*FunctionPtr)(
		args[0].GetValue<Arg1>()
		);
}

template <typename FunctionType, FunctionType FunctionPtr, typename C, typename Arg1, typename Arg2>
void CallMethodVoid(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 2);
	(((C *)context)->*FunctionPtr)(
		args[0].GetValue<Arg1>(),
		args[1].GetValue<Arg2>()
		);
}

template <typename FunctionType, FunctionType FunctionPtr, typename C, typename Arg1, typename Arg2, typename Arg3>
void CallMethodVoid(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 3);
	(((C *)context)->*FunctionPtr)(
		args[0].GetValue<Arg1>(),
		args[1].GetValue<Arg2>(),
		args[2].GetValue<Arg3>()
		);
}

template <typename FunctionType, FunctionType FunctionPtr, typename C, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
void CallMethodVoid(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 4);
	(((C *)context)->*FunctionPtr)(
		args[0].GetValue<Arg1>(),
		args[1].GetValue<Arg2>(),
		args[2].GetValue<Arg3>(),
		args[3].GetValue<Arg4>()
		);
}

template <typename FunctionType, FunctionType FunctionPtr, typename C, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
void CallMethodVoid(Variable *ret, void *context, Variable *args, unsigned argCount)
{
	assert(argCount == 5);
	(((C *)context)->*FunctionPtr)(
		args[0].GetValue<Arg1>(),
		args[1].GetValue<Arg2>(),
		args[2].GetValue<Arg3>(),
		args[3].GetValue<Arg4>(),
		args[4].GetValue<Arg5>()
		);
}

// Build static functions with return value
template <typename FunctionType, FunctionType FunctionPtr, typename R>
Function BuildFunction(R(*fn)(void))
{
	return Function(fn, &Call<FunctionType, FunctionPtr, R>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename Arg1>
Function BuildFunction(R(*fn)(Arg1))
{
	return Function(fn, &Call<FunctionType, FunctionPtr, R, Arg1>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename Arg1, typename Arg2>
Function BuildFunction(R(*fn)(Arg1, Arg2))
{
	return Function(fn, &Call<FunctionType, FunctionPtr, R, Arg1, Arg2>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename Arg1, typename Arg2, typename Arg3>
Function BuildFunction(R(*fn)(Arg1, Arg2, Arg3))
{
	return Function(fn, &Call<FunctionType, FunctionPtr, R, Arg1, Arg2, Arg3>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
Function BuildFunction(R(*fn)(Arg1, Arg2, Arg3, Arg4))
{
	return Function(fn, &Call<FunctionType, FunctionPtr, R, Arg1, Arg2, Arg3, Arg4>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
Function BuildFunction(R(*fn)(Arg1, Arg2, Arg3, Arg4, Arg5))
{
	return Function(fn, &Call<FunctionType, FunctionPtr, R, Arg1, Arg2, Arg3, Arg4, Arg5>);
}

// Build static functions without return value
template <typename FunctionType, FunctionType FunctionPtr>
Function BuildFunction(void(*fn)(void))
{
	return Function(fn, &CallVoid<FunctionType, FunctionPtr>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename Arg1>
Function BuildFunction(void(*fn)(Arg1))
{
	return Function(fn, &CallVoid<FunctionType, FunctionPtr, Arg1>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename Arg1, typename Arg2>
Function BuildFunction(void(*fn)(Arg1, Arg2))
{
	return Function(fn, &CallVoid<FunctionType, FunctionPtr, Arg1, Arg2>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename Arg1, typename Arg2, typename Arg3>
Function BuildFunction(void(*fn)(Arg1, Arg2, Arg3))
{
	return Function(fn, &CallVoid<FunctionType, FunctionPtr, Arg1, Arg2, Arg3>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
Function BuildFunction(void(*fn)(Arg1, Arg2, Arg3, Arg4))
{
	return Function(fn, &CallVoid<FunctionType, FunctionPtr, Arg1, Arg2, Arg3, Arg4>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
Function BuildFunction(void(*fn)(Arg1, Arg2, Arg3, Arg4, Arg5))
{
	return Function(fn, &CallVoid<FunctionType, FunctionPtr, Arg1, Arg2, Arg3, Arg4, Arg5>);
}

// Build methods with return value, non-const
template <typename FunctionType, FunctionType FunctionPtr, typename R, typename C>
Function BuildFunction(R(C::*fn)(void))
{
	return Function(fn, &CallMethod<FunctionType, FunctionPtr, R, C>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename C, typename Arg1>
Function BuildFunction(R(C::*fn)(Arg1))
{
	return Function(fn, &CallMethod<FunctionType, FunctionPtr, R, C, Arg1>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename C, typename Arg1, typename Arg2>
Function BuildFunction(R(C::*fn)(Arg1, Arg2))
{
	return Function(fn, &CallMethod<FunctionType, FunctionPtr, R, C, Arg1, Arg2>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename C, typename Arg1, typename Arg2, typename Arg3>
Function BuildFunction(R(C::*fn)(Arg1, Arg2, Arg3))
{
	return Function(fn, &CallMethod<FunctionType, FunctionPtr, R, C, Arg1, Arg2, Arg3>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename C, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
Function BuildFunction(R(C::*fn)(Arg1, Arg2, Arg3, Arg4))
{
	return Function(fn, &CallMethod<FunctionType, FunctionPtr, R, C, Arg1, Arg2, Arg3, Arg4>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename C, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
Function BuildFunction(R(C::*fn)(Arg1, Arg2, Arg3, Arg4, Arg5))
{
	return Function(fn, &CallMethod<FunctionType, FunctionPtr, R, C, Arg1, Arg2, Arg3, Arg4, Arg5>);
}

// Build methods with return value, const
template <typename FunctionType, FunctionType FunctionPtr, typename R, typename C>
Function BuildFunction(R(C::*fn)(void) const)
{
	return Function(fn, &CallMethod<FunctionType, FunctionPtr, R, C>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename C, typename Arg1>
Function BuildFunction(R(C::*fn)(Arg1) const)
{
	return Function(fn, &CallMethod<FunctionType, FunctionPtr, R, C, Arg1>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename C, typename Arg1, typename Arg2>
Function BuildFunction(R(C::*fn)(Arg1, Arg2) const)
{
	return Function(fn, &CallMethod<FunctionType, FunctionPtr, R, C, Arg1, Arg2>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename C, typename Arg1, typename Arg2, typename Arg3>
Function BuildFunction(R(C::*fn)(Arg1, Arg2, Arg3) const)
{
	return Function(fn, &CallMethod<FunctionType, FunctionPtr, R, C, Arg1, Arg2, Arg3>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename C, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
Function BuildFunction(R(C::*fn)(Arg1, Arg2, Arg3, Arg4) const)
{
	return Function(fn, &CallMethod<FunctionType, FunctionPtr, R, C, Arg1, Arg2, Arg3, Arg4>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename R, typename C, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
Function BuildFunction(R(C::*fn)(Arg1, Arg2, Arg3, Arg4, Arg5) const)
{
	return Function(fn, &CallMethod<FunctionType, FunctionPtr, R, C, Arg1, Arg2, Arg3, Arg4, Arg5>);
}

// Build methods without return value, non-const
template <typename FunctionType, FunctionType FunctionPtr, typename C>
Function BuildFunction(void (C::*fn)(void))
{
	return Function(fn, &CallMethodVoid<FunctionType, FunctionPtr, C>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename C, typename Arg1>
Function BuildFunction(void (C::*fn)(Arg1))
{
	return Function(fn, &CallMethodVoid<FunctionType, FunctionPtr, C, Arg1>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename C, typename Arg1, typename Arg2>
Function BuildFunction(void (C::*fn)(Arg1, Arg2))
{
	return Function(fn, &CallMethodVoid<FunctionType, FunctionPtr, C, Arg1, Arg2>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename C, typename Arg1, typename Arg2, typename Arg3>
Function BuildFunction(void (C::*fn)(Arg1, Arg2, Arg3))
{
	return Function(fn, &CallMethodVoid<FunctionType, FunctionPtr, C, Arg1, Arg2, Arg3>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename C, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
Function BuildFunction(void (C::*fn)(Arg1, Arg2, Arg3, Arg4))
{
	return Function(fn, &CallMethodVoid<FunctionType, FunctionPtr, C, Arg1, Arg2, Arg3, Arg4>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename C, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
Function BuildFunction(void (C::*fn)(Arg1, Arg2, Arg3, Arg4, Arg5))
{
	return Function(fn, &CallMethodVoid<FunctionType, FunctionPtr, C, Arg1, Arg2, Arg3, Arg4, Arg5>);
}

// Build methods without return value, const
template <typename FunctionType, FunctionType FunctionPtr, typename C>
Function BuildFunction(void (C::*fn)(void) const)
{
	return Function(fn, &CallMethodVoid<FunctionType, FunctionPtr, C>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename C, typename Arg1>
Function BuildFunction(void (C::*fn)(Arg1) const)
{
	return Function(fn, &CallMethodVoid<FunctionType, FunctionPtr, C, Arg1>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename C, typename Arg1, typename Arg2>
Function BuildFunction(void (C::*fn)(Arg1, Arg2) const)
{
	return Function(fn, &CallMethodVoid<FunctionType, FunctionPtr, C, Arg1, Arg2>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename C, typename Arg1, typename Arg2, typename Arg3>
Function BuildFunction(void (C::*fn)(Arg1, Arg2, Arg3) const)
{
	return Function(fn, &CallMethodVoid<FunctionType, FunctionPtr, C, Arg1, Arg2, Arg3>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename C, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
Function BuildFunction(void (C::*fn)(Arg1, Arg2, Arg3, Arg4) const)
{
	return Function(fn, &CallMethodVoid<FunctionType, FunctionPtr, C, Arg1, Arg2, Arg3, Arg4>);
}

template <typename FunctionType, FunctionType FunctionPtr, typename C, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
Function BuildFunction(void (C::*fn)(Arg1, Arg2, Arg3, Arg4, Arg5) const)
{
	return Function(fn, &CallMethodVoid<FunctionType, FunctionPtr, C, Arg1, Arg2, Arg3, Arg4, Arg5>);
}