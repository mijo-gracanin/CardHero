//
//  CardAnimation.h
//  CardHero
//
//  Created by Mijo Gracanin on 20/01/2019.
//  Copyright © 2019 MijoCoder. All rights reserved.
//

#ifndef CardAnimation_h
#define CardAnimation_h


namespace as {
    
    class CardAnimation {
    public:
        virtual ~CardAnimation()=0;
        virtual void update(float dt)=0;
        virtual bool getIsCompleted() const=0;
    };
    
    inline CardAnimation::~CardAnimation() { }
    
}

#endif /* CardAnimation_h */
