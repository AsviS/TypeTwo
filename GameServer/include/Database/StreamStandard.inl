template<typename Procedure>
Stream<Procedure>::Stream(const Procedure& procedure)
: mProcedure(procedure)
, mStream(mProcedure.createStreamPtr())
{

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
std::vector<RowType> Stream<Procedure>::execute(ParamTypes... params)
{
    return mProcedure.execute<RowType>(*mStream, params...);
}

///////////////////////////////////

template<typename Procedure>
Stream<Procedure> create(const Procedure& procedure)
{
    return Stream<Procedure>(procedure);
}
