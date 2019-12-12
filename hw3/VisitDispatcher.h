#pragma once

#include "Functor.h"
#include "TypeList.h"
#include "Utils.h"

// To use VisitDispatcher define template instantiations with proper args
template <class ResultType, class Visitor, class Acceptor, class... Args>
class VisitFunctor : IFunctor<ResultType, Visitor*, Acceptor*, Args...> {
public:
    ResultType operator()(Visitor* visitor, Acceptor* acceptor, Args... args) override {
        std::cout << "Error! Cannot accept " << visitor->VisitorType() << " visitor by "
            << acceptor->AcceptorType() << " acceptor with these arguments: ";
        PrintArgs(std::cout, args...);
    }
};

template <class Visitor, class VisitorsTL, class Acceptor, class AcceptorsTL, class AcceptResultType, class ResultType, class... Args>
class VisitDispatcher;

template <class Visitor, class VH, class... VT, class Acceptor, class AH, class... AT, class AcceptResultType, class ResultType, class... Args>
class VisitDispatcher<Visitor, TypeList<VH, VT...>, Acceptor, TypeList<AH, AT...>, AcceptResultType, ResultType, Args...> {
public:
    static ResultType Go(Visitor* visitor, Acceptor* acceptor, Args... args) {
        return DispatchVisitor(visitor, acceptor, args...);
    }

    static ResultType DispatchVisitor(Visitor* visitor, Acceptor* acceptor, Args... args) {
        auto head_visitor = dynamic_cast<VH*>(visitor);
        if (head_visitor) {
            return DispatchAcceptor(visitor, acceptor, args...);
        } else {
            return VisitDispatcher<Visitor, TypeList<VT...>, Acceptor, TypeList<AH, AT...>, AcceptResultType, ResultType, Args...>
                ::DispatchVisitor(visitor, acceptor, args...);
        }
    }
    static ResultType DispatchAcceptor(Visitor* visitor, Acceptor* acceptor, Args... args) {
        auto head_acceptor = dynamic_cast<AH*>(acceptor);
        if (head_acceptor) {
            AcceptResultType accept_result = acceptor->Accept(visitor);
            VisitFunctor<ResultType, VH, AH, AcceptResultType, Args...> functor;
            return functor(static_cast<VH*>(visitor), head_acceptor, accept_result, args...);
        } else {
            return VisitDispatcher<Visitor, TypeList<VH, VT...>, Acceptor, TypeList<AT...>, AcceptResultType, ResultType, Args...>
                ::DispatchAcceptor(visitor, acceptor, args...);
        }
    }
};

template <class Visitor, class VH, class Acceptor, class AH, class... AT, class AcceptResultType, class ResultType, class... Args>
class VisitDispatcher<Visitor, TypeList<VH>, Acceptor, TypeList<AH, AT...>, AcceptResultType, ResultType, Args...> {
public:
    static ResultType Go(Visitor* visitor, Acceptor* acceptor, Args... args) {
        return DispatchVisitor(visitor, acceptor, args...);
    }

    static ResultType DispatchVisitor(Visitor* visitor, Acceptor* acceptor, Args... args) {
        auto head_visitor = dynamic_cast<VH*>(visitor);
        if (head_visitor) {
            return DispatchAcceptor(visitor, acceptor, args...);
        } else {
            return ResultType();
        }
    }
    static ResultType DispatchAcceptor(Visitor* visitor, Acceptor* acceptor, Args... args) {
        auto head_acceptor = dynamic_cast<AH*>(acceptor);
        if (head_acceptor) {
            AcceptResultType accept_result = acceptor->Accept(visitor);
            VisitFunctor<ResultType, VH, AH, AcceptResultType, Args...> functor;
            return functor(static_cast<VH*>(visitor), head_acceptor, accept_result, args...);
        } else {
            return VisitDispatcher<Visitor, TypeList<VH>, Acceptor, TypeList<AT...>, AcceptResultType, ResultType, Args...>
            ::DispatchAcceptor(visitor, acceptor, args...);
        }
    }
};

template <class Visitor, class VH, class... VT, class Acceptor, class AH, class AcceptResultType, class ResultType, class... Args>
class VisitDispatcher<Visitor, TypeList<VH, VT...>, Acceptor, TypeList<AH>, AcceptResultType, ResultType, Args...> {
public:
    static ResultType Go(Visitor* visitor, Acceptor* acceptor, Args... args) {
        return DispatchVisitor(visitor, acceptor, args...);
    }

    static ResultType DispatchVisitor(Visitor* visitor, Acceptor* acceptor, Args... args) {
        auto head_visitor = dynamic_cast<VH*>(visitor);
        if (head_visitor) {
            return DispatchAcceptor(visitor, acceptor, args...);
        } else {
            return VisitDispatcher<Visitor, TypeList<VT...>, Acceptor, TypeList<AH>, AcceptResultType, ResultType, Args...>
            ::DispatchVisitor(visitor, acceptor, args...);
        }
    }
    static ResultType DispatchAcceptor(Visitor* visitor, Acceptor* acceptor, Args... args) {
        auto head_acceptor = dynamic_cast<AH*>(acceptor);
        if (head_acceptor) {
            AcceptResultType accept_result = acceptor->Accept(visitor);
            VisitFunctor<ResultType, VH, AH, AcceptResultType, Args...> functor;
            return functor(static_cast<VH*>(visitor), head_acceptor, accept_result, args...);
        } else {
            return ResultType();
        }
    }
};

template <class Visitor, class VH, class Acceptor, class AH, class AcceptResultType, class ResultType, class... Args>
class VisitDispatcher<Visitor, TypeList<VH>, Acceptor, TypeList<AH>, AcceptResultType, ResultType, Args...> {
public:
    static ResultType Go(Visitor* visitor, Acceptor* acceptor, Args... args) {
        return DispatchVisitor(visitor, acceptor, args...);
    }

    static ResultType DispatchVisitor(Visitor* visitor, Acceptor* acceptor, Args... args) {
        auto head_visitor = dynamic_cast<VH*>(visitor);
        if (head_visitor) {
            return DispatchAcceptor(visitor, acceptor, args...);
        } else {
            return ResultType();
        }
    }
    static ResultType DispatchAcceptor(Visitor* visitor, Acceptor* acceptor, Args... args) {
        auto head_acceptor = dynamic_cast<AH*>(acceptor);
        if (head_acceptor) {
            AcceptResultType accept_result = acceptor->Accept(visitor);
            VisitFunctor<ResultType, VH, AH, AcceptResultType, Args...> functor;
            return functor(static_cast<VH*>(visitor), head_acceptor, accept_result, args...);
        } else {
            return ResultType();
        }
    }
};