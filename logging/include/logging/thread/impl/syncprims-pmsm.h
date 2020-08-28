#if ! defined (INSIDE_LOGGING)
#  error "This header must not be be used outside logging' implementation files."
#endif


// This implements algorithm described in "Concurrent Control with "Readers"
// and "Writers"; P.J. Courtois, F. Heymans, and D.L. Parnas;
// MBLE Research Laboratory; Brussels, Belgium"


inline
SharedMutex::SharedMutex()
	: m1()
	, m2()
	, m3()
	, w(1, 1)
	, writer_count(0)
	, r(1, 1)
	, reader_count(0)
{ }


inline
SharedMutex::~SharedMutex()
{ }


inline
void
SharedMutex::rdlock() const
{
	MutexGuard m3_guard(m3);
	SemaphoreGuard r_guard(r);
	MutexGuard m1_guard(m1);
	if (reader_count + 1 == 1)
		w.lock();

	reader_count += 1;
}


inline
void
SharedMutex::rdunlock() const
{
	MutexGuard m1_guard(m1);
	if (reader_count - 1 == 0)
		w.unlock();

	reader_count -= 1;
}


inline
void
SharedMutex::wrlock() const
{
	{
		MutexGuard m2_guard(m2);
		if (writer_count + 1 == 1)
			r.lock();

		writer_count += 1;
	}
	try
	{
		w.lock();
	}
	catch (...)
	{
		MutexGuard m2_guard(m2);
		writer_count -= 1;
		throw;
	}
}


inline
void
SharedMutex::wrunlock() const
{
	w.unlock();
	MutexGuard m2_guard(m2);
	if (writer_count - 1 == 0)
		r.unlock();

	writer_count -= 1;
}
