#pragma once  

namespace inventory {  

    class IDisplayable {
    public:
        virtual void display() const = 0;
        virtual ~IDisplayable() = default;
    };

} 