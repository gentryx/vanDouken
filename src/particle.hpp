//  Copyright (c) 2012-2013 Thomas Heller
//  Copyright (c) 2012-2013 Andreas Schaefer
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef VANDOUKEN_PARTICLE_HPP
#define VANDOUKEN_PARTICLE_HPP

#include <libgeodecomp/misc/supervector.h>
#include <libgeodecomp/misc/topologies.h>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#if !defined(__ANDROID__) || !defined(ANDROID)
#include <QColor>
#else
inline int qRed(unsigned int rgb)
{
    return ((rgb >> 16) & 0xff);
}

inline int qGreen(unsigned int rgb)
{
    return ((rgb >> 8) & 0xff);
}

inline int qBlue(unsigned int rgb)
{
    return (rgb & 0xff);
}

inline int qAlpha(unsigned int rgb)
{
    return rgb >> 24;
}
#endif


namespace vandouken {
    class Particle
    {
    public:
        inline Particle(float posX=0, float posY=0, float posZ=0, float angle=0, unsigned color=0) :
            posX (posX ),
            posY (posY ),
            posZ (posZ ),
            angle(angle),
            color(color)
        {}

        float posX;
        float posY;
        float posZ;
        float angle;
        // coding: AARRGGBB, use color for color multiply of texture and alpha for texture index?
        unsigned color;
    };

    class Particles
    {
    public:
        typedef LibGeoDecomp::Topologies::Cube<2>::Topology Topology;

        Particles() :
            posAngle(boost::make_shared<LibGeoDecomp::SuperVector<float> >()),
            colors(boost::make_shared<LibGeoDecomp::SuperVector<boost::uint32_t> >())
        {}

        bool addParticle(std::size_t i, const Particle& particle)
        {
            /*
            if(qAlpha(particle.color) < 229)
                return false;
            */

            (*posAngle)[i * 4 + 0] = std::ceil(particle.posX * 100.f);
            (*posAngle)[i * 4 + 1] = std::ceil(particle.posY * 100.f);
            (*posAngle)[i * 4 + 2] = std::ceil(particle.posZ * 100.f);
            (*posAngle)[i * 4 + 3] = std::ceil(particle.angle * 100.f);

            (*colors)[i] = particle.color;
            return true;
        }

        void resize(std::size_t size)
        {
            posAngle->resize(size * 4);
            colors->resize(size);
        }

        std::size_t size()
        {
            return posAngle->size() / 4;
        }

        template<typename ARCHIVE>
        void serialize(ARCHIVE& ar, unsigned)
        {
            ar & posAngle;
            ar & colors;
        }

        boost::shared_ptr<LibGeoDecomp::SuperVector<float> > posAngle;
        boost::shared_ptr<LibGeoDecomp::SuperVector<boost::uint32_t> > colors;
    };
}
BOOST_IS_BITWISE_SERIALIZABLE(vandouken::Particle)

#endif