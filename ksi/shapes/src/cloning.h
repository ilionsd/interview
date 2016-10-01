#ifndef _CLONING_H_
#define _CLONING_H_

#include <memory>

namespace cloning {

    template<typename TBase>
    struct cloneable {
		using base_t = TBase;

		virtual std::unique_ptr<base_t>
        clone() = 0;
    };

    template<typename TDer, typename TBase>
    struct cloner :
        public virtual cloneable<TBase>
    {
		using derived_t = TDer;

		virtual std::unique_ptr<base_t>
		clone() override {
            derived_t *derivedPtr = static_cast<derived_t*>(this);
			std::unique_ptr<base_t> derivedClone(new derived_t(*derivedPtr));
            return derivedClone;
        };
    };

};  //-- namespace cloning --

#endif // _CLONING_H_
