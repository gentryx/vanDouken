#ifndef VANDOUKEN_IMAGESTEERER_HPP
#define VANDOUKEN_IMAGESTEERER_HPP

#include "config.hpp"
#include "cell.hpp"

#include <libgeodecomp/geometry/floatcoord.h>
#include <libgeodecomp/geometry/region.h>
#include <libgeodecomp/storage/gridbase.h>

#include <QImage>
#include <QBuffer>

namespace vandouken {

    using LibGeoDecomp::Coord;
    using LibGeoDecomp::FloatCoord;
    using LibGeoDecomp::Region;
    using LibGeoDecomp::Streak;

    struct ImageSteerer
    {
        ImageSteerer() {}

        ImageSteerer(boost::shared_ptr<QImage> image, bool clear = true)
          : image(image)
          , clear(clear)
        {}

        void operator()(
                LibGeoDecomp::GridBase<Cell, 2> *grid,
                const LibGeoDecomp::Region<2>& validRegion,
                const LibGeoDecomp::Coord<2>& globalDimensions,
                unsigned)
        {
            QImage tmp = image->scaled(globalDimensions.x(), globalDimensions.y());

            FloatCoord<2> force(0.0f, 0.0f);
            LibGeoDecomp::CoordBox<2> box = grid->boundingBox();
            for (LibGeoDecomp::CoordBox<2>::Iterator i = box.begin(); i != box.end(); ++i) {
                if(clear)
                {
                    grid->set(*i,
                        Cell(
                            0xff000000 + tmp.pixel(i->x(), i->y())
                          , *i
                          , false
                          , force
                          , rand() % Cell::MAX_SPAWN_COUNTDOWN
                        )
                    );
                }
                else
                {
                    Cell cell = grid->get(*i);
                    cell.backgroundPixel
                        = 0xff000000 + tmp.pixel(i->x(), i->y());
                    for(int j = 0; j < cell.numParticles; ++j)
                    {
                        if(cell.particles[j].lifetime > DEFAULT_PARTICLE_LIFETIME/2)
                        {
                            cell.particles[j].color = 0xff000000 + tmp.pixel(i->x(), i->y());
                        }
                    }
                    grid->set(*i, cell);
                }
            }
        }

        boost::shared_ptr<QImage> image;
        bool clear;

        template <typename ARCHIVE>
        void save(ARCHIVE& ar, unsigned) const
        {
            QByteArray ba;
            QBuffer buffer(&ba);
            buffer.open(QIODevice::WriteOnly);
            image->save(&buffer, "PNG");
            int size = ba.size();
            ar & size;
            ar & boost::serialization::make_array(ba.data(), ba.size());
            ar & clear;
        }

        template <typename ARCHIVE>
        void load(ARCHIVE& ar, unsigned)
        {
            int size = 0;
            ar & size;
            QByteArray ba(size, 0);
            ar & boost::serialization::make_array(ba.data(), size);
            QBuffer buffer(&ba);
            buffer.open(QIODevice::ReadOnly);
            image.reset(new QImage);
            image->load(&buffer, "PNG");
            ar & clear;
        }

        BOOST_SERIALIZATION_SPLIT_MEMBER()
    };
}

#endif
