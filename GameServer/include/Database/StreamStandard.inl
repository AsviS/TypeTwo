template<typename Procedure>
Stream<Procedure>::Stream(const Procedure& procedure)
: mProcedure(procedure)
, mStream(mProcedure.createStreamPtr())
{
    mStream->set_commit(0);
}

///////////////////////////////////

template<typename Procedure>
Stream<Procedure>::~Stream()
{
    commit();
}

///////////////////////////////////

template<typename Procedure>
template<typename... ParamTypes>
void Stream<Procedure>::execute(ParamTypes... params)
{
    mProcedure.execute(*mStream, params...);
}

///////////////////////////////////

template<typename Procedure>
template<typename RowType, typename... ParamTypes>
void Stream<Procedure>::execute(std::vector<RowType>& rows, ParamTypes... params)
{
    mProcedure.execute<RowType>(*mStream, rows, params...);
}

///////////////////////////////////

template <typename Procedure>
void Stream<Procedure>::commit() const
{
    mProcedure.commit();
}

///////////////////////////////////

template<typename Procedure>
Stream<Procedure> create(const Procedure& procedure)
{
    return Stream<Procedure>(procedure);
}
