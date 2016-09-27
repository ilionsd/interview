#ifndef _CLONING_H_
#define _CLONING_H_

#include <memory>

namespace cloning {

    template<typename TBase>
    struct cloneable {
		virtual std::unique_ptr<TBase>
        clone() = 0;
    };

    template<typename TDer, typename TBase>
    struct cloner :
        public virtual cloneable<TBase>
    {
		virtual std::unique_ptr<TBase>
		clone() override {
            TDer *derivedPtr = static_cast<TDer*>(this);
            std::unique_ptr<TDer> derivedClone = std::make_unique<TDer>(*derivedPtr);
            return derivedClone;
        };
    };

};  //-- namespace cloning --

#endif // _CLONING_H_
