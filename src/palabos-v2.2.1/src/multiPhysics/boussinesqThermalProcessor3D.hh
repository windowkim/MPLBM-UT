/* This file is part of the Palabos library.
 *
 * The Palabos softare is developed since 2011 by FlowKit-Numeca Group Sarl
 * (Switzerland) and the University of Geneva (Switzerland), which jointly
 * own the IP rights for most of the code base. Since October 2019, the
 * Palabos project is maintained by the University of Geneva and accepts
 * source code contributions from the community.
 * 
 * Contact:
 * Jonas Latt
 * Computer Science Department
 * University of Geneva
 * 7 Route de Drize
 * 1227 Carouge, Switzerland
 * jonas.latt@unige.ch
 *
 * The most recent release of Palabos can be downloaded at 
 * <https://palabos.unige.ch/>
 *
 * The library Palabos is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * The library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BOUSSINESQ_THERMAL_PROCESSOR_3D_HH
#define BOUSSINESQ_THERMAL_PROCESSOR_3D_HH

#include "multiPhysics/boussinesqThermalProcessor3D.h"
#include "atomicBlock/blockLattice3D.h"
#include "core/util.h"
#include "finiteDifference/finiteDifference3D.h"
#include "latticeBoltzmann/geometricOperationTemplates.h"

namespace plb {

template< typename T,
          template<typename U1> class FluidDescriptor, 
          template<typename U2> class TemperatureDescriptor
        >
BoussinesqThermalProcessor3D<T,FluidDescriptor,TemperatureDescriptor>::
        BoussinesqThermalProcessor3D(T gravity_, T T0_, T deltaTemp_, Array<T,FluidDescriptor<T>::d> dir_)
    :  gravity(gravity_), T0(T0_), deltaTemp(deltaTemp_),
       dir(dir_)
{
    // We normalize the direction of the force vector.
    T normDir = std::sqrt(VectorTemplate<T,FluidDescriptor>::normSqr(dir));
    for (pluint iD = 0; iD < FluidDescriptor<T>::d; ++iD) {
        dir[iD] /= normDir;
    }
}

template< typename T,
          template<typename U1> class FluidDescriptor, 
          template<typename U2> class TemperatureDescriptor
        >
void BoussinesqThermalProcessor3D<T,FluidDescriptor,TemperatureDescriptor>::process (
        Box3D domain,
        BlockLattice3D<T,FluidDescriptor>& fluid,
        BlockLattice3D<T,TemperatureDescriptor>& temperature )
{
    typedef FluidDescriptor<T> D;
    enum {
        velOffset   = TemperatureDescriptor<T>::ExternalField::velocityBeginsAt,
        forceOffset = FluidDescriptor<T>::ExternalField::forceBeginsAt
    };
    Dot3D offset = computeRelativeDisplacement(fluid, temperature);
    
    Array<T,D::d> gravOverDeltaTemp (
            gravity*dir[0]/deltaTemp,
            gravity*dir[1]/deltaTemp,
            gravity*dir[2]/deltaTemp );
           
    for (plint iX=domain.x0; iX<=domain.x1; ++iX) 
    {
        for (plint iY=domain.y0; iY<=domain.y1; ++iY) 
        {
            for (plint iZ=domain.z0; iZ<=domain.z1; ++iZ) 
            {
                // Velocity coupling
                T *u = temperature.get(iX+offset.x,iY+offset.y,iZ+offset.z).getExternal(velOffset);
                Array<T,FluidDescriptor<T>::d> vel;
                fluid.get(iX,iY,iZ).computeVelocity(vel);
                vel.to_cArray(u);
                
                // Computation of the Boussinesq force
                T *force = fluid.get(iX,iY,iZ).getExternal(forceOffset);
                // Temperature is the order-0 moment of the advection-diffusion lattice.
                //   You can compute it with the method computeDensity().
                T localTemperature = temperature.get(iX+offset.x,iY+offset.y,iZ+offset.z).computeDensity();
                const T diffT = localTemperature - T0;
                for (pluint iD = 0; iD < D::d; ++iD) 
                {
                    force[iD] = gravOverDeltaTemp[iD] * diffT;
                }
            }
        }
    }
}

template< typename T,
          template<typename U1> class FluidDescriptor, 
          template<typename U2> class TemperatureDescriptor
        >
BoussinesqThermalProcessor3D<T,FluidDescriptor,TemperatureDescriptor>*
    BoussinesqThermalProcessor3D<T,FluidDescriptor,TemperatureDescriptor>::clone() const
{
    return new BoussinesqThermalProcessor3D<T,FluidDescriptor,TemperatureDescriptor>(*this);
}



template< typename T,
          template<typename U1> class FluidDescriptor, 
          template<typename U2> class TemperatureDescriptor
        >
CompleteBoussinesqThermalProcessor3D<T,FluidDescriptor,TemperatureDescriptor>::
        CompleteBoussinesqThermalProcessor3D(T gravity_, T T0_, T deltaTemp_, Array<T,FluidDescriptor<T>::d> dir_)
    :  gravity(gravity_), T0(T0_), deltaTemp(deltaTemp_),
       dir(dir_)
{
    // We normalize the direction of the force vector.
    T normDir = std::sqrt(VectorTemplate<T,FluidDescriptor>::normSqr(dir));
    for (pluint iD = 0; iD < FluidDescriptor<T>::d; ++iD) {
        dir[iD] /= normDir;
    }
}

template< typename T,
          template<typename U1> class FluidDescriptor, 
          template<typename U2> class TemperatureDescriptor
        >
void CompleteBoussinesqThermalProcessor3D<T,FluidDescriptor,TemperatureDescriptor>::process (
        Box3D domain,
        BlockLattice3D<T,FluidDescriptor>& fluid,
        BlockLattice3D<T,TemperatureDescriptor>& temperature )
{
    typedef FluidDescriptor<T> D;
    enum {
        rhoBarOffset   = TemperatureDescriptor<T>::ExternalField::rhoBarBeginsAt,
        velocityOffset = TemperatureDescriptor<T>::ExternalField::velocityBeginsAt,
        piNeqOffset    = TemperatureDescriptor<T>::ExternalField::piNeqBeginsAt,
        omegaOffset    = TemperatureDescriptor<T>::ExternalField::omegaBeginsAt,
        forceOffset    = FluidDescriptor<T>::ExternalField::forceBeginsAt
    };
    Dot3D offset = computeRelativeDisplacement(fluid, temperature);
    
    Array<T,D::d> gravOverDeltaTemp (
            gravity*dir[0]/deltaTemp,
            gravity*dir[1]/deltaTemp,
            gravity*dir[2]/deltaTemp );
           
    for (plint iX=domain.x0; iX<=domain.x1; ++iX) 
    {
        for (plint iY=domain.y0; iY<=domain.y1; ++iY) 
        {
            for (plint iZ=domain.z0; iZ<=domain.z1; ++iZ) 
            {
                // Computation of the Boussinesq force
                T *force = fluid.get(iX,iY,iZ).getExternal(forceOffset);
                // Temperature is the order-0 moment of the advection-diffusion lattice.
                //   You can compute it with the method computeDensity().
                T localTemperature = temperature.get(iX+offset.x,iY+offset.y,iZ+offset.z).computeDensity();
                const T diffT = localTemperature - T0;
                for (pluint iD = 0; iD < D::d; ++iD) {
                    force[iD] = gravOverDeltaTemp[iD] * diffT;
                }

                // Velocity coupling
                T rhoBar;
                Array<T,FluidDescriptor<T>::d> j;
                Array<T,SymmetricTensor<T,FluidDescriptor>::n> piNeq;
                
                fluid.get(iX,iY,iZ).getDynamics().computeRhoBarJPiNeq(fluid.get(iX,iY,iZ),rhoBar,j,piNeq);
                for (plint iD = 0; iD < D::d; ++iD) {
                    j[iD] += D::fullRho(rhoBar)*force[iD]*(T)0.5;
                }

                Array<T,FluidDescriptor<T>::d> vel = FluidDescriptor<T>::invRho(rhoBar) * j;
                
                *temperature.get(iX+offset.x,iY+offset.y,iZ+offset.z).getExternal(omegaOffset) = fluid.get(iX,iY,iZ).getDynamics().getOmega();
                *temperature.get(iX+offset.x,iY+offset.y,iZ+offset.z).getExternal(rhoBarOffset) = rhoBar;
                vel.to_cArray(temperature.get(iX+offset.x,iY+offset.y,iZ+offset.z).getExternal(velocityOffset));
                piNeq.to_cArray(temperature.get(iX+offset.x,iY+offset.y,iZ+offset.z).getExternal(piNeqOffset));

            }
        }
    }
}

template< typename T,
          template<typename U1> class FluidDescriptor, 
          template<typename U2> class TemperatureDescriptor
        >
CompleteBoussinesqThermalProcessor3D<T,FluidDescriptor,TemperatureDescriptor>*
    CompleteBoussinesqThermalProcessor3D<T,FluidDescriptor,TemperatureDescriptor>::clone() const
{
    return new CompleteBoussinesqThermalProcessor3D<T,FluidDescriptor,TemperatureDescriptor>(*this);
}

/*
template< typename T,
          template<typename U1> class FluidDescriptor, 
          template<typename U2> class TemperatureDescriptor
        >
SmagorinskyBoussinesqThermalProcessor3D<T,FluidDescriptor,TemperatureDescriptor>::
        SmagorinskyBoussinesqThermalProcessor3D(T gravity_, T T0_, T deltaTemp_, Array<T,FluidDescriptor<T>::d> dir_,
        T cSmagoFluid_, T cSmagoTemp_ )
    :  gravity(gravity_), T0(T0_), deltaTemp(deltaTemp_),
       dir(dir_),
       cSmagoFluid(cSmagoFluid_),
       cSmagoTemp(cSmagoTemp_),
       nu0(nu0_), d0(d0_)
{
    // We normalize the direction of the force vector.
    T normDir = std::sqrt(VectorTemplate<T,FluidDescriptor>::normSqr(dir));
    for (pluint iD = 0; iD < FluidDescriptor<T>::d; ++iD) {
        dir[iD] /= normDir;
    }
}

template< typename T,
          template<typename U1> class FluidDescriptor, 
          template<typename U2> class TemperatureDescriptor
        >
void SmagorinskyBoussinesqThermalProcessor3D<T,FluidDescriptor,TemperatureDescriptor>::process (
        Box3D domain,
        BlockLattice3D<T,FluidDescriptor>& fluid,
        BlockLattice3D<T,TemperatureDescriptor>& temperature )
{
    typedef FluidDescriptor<T> D;
    enum {
        velOffset   = TemperatureDescriptor<T>::ExternalField::velocityBeginsAt,
        forceOffset = FluidDescriptor<T>::ExternalField::forceBeginsAt
    };
    Dot3D offset = computeRelativeDisplacement(fluid, temperature);
    
    Array<T,D::d> gravOverDeltaTemp (
            gravity*dir[0]/deltaTemp,
            gravity*dir[1]/deltaTemp,
            gravity*dir[2]/deltaTemp );
           
    for (plint iX=domain.x0; iX<=domain.x1; ++iX) 
    {
        for (plint iY=domain.y0; iY<=domain.y1; ++iY) 
        {
            for (plint iZ=domain.z0; iZ<=domain.z1; ++iZ) 
            {
                // Velocity coupling
                T *u = temperature.get(iX+offset.x,iY+offset.y,iZ+offset.z).getExternal(velOffset);
                Array<T,FluidDescriptor<T>::d> vel;
                fluid.get(iX,iY,iZ).computeVelocity(vel);
                vel.to_cArray(u);
                
                // Computation of the Boussinesq force
                T *force = fluid.get(iX,iY,iZ).getExternal(forceOffset);
                // Temperature is the order-0 moment of the advection-diffusion lattice.
                //   You can compute it with the method computeDensity().
                T localTemperature = temperature.get(iX+offset.x,iY+offset.y,iZ+offset.z).computeDensity();
                const T diffT = localTemperature - T0;
                for (pluint iD = 0; iD < D::d; ++iD) 
                {
                    force[iD] = gravOverDeltaTemp[iD] * diffT;
                }
            }
        }
    }
}

template< typename T,
          template<typename U1> class FluidDescriptor, 
          template<typename U2> class TemperatureDescriptor
        >
SmagorinskyBoussinesqThermalProcessor3D<T,FluidDescriptor,TemperatureDescriptor>*
    SmagorinskyBoussinesqThermalProcessor3D<T,FluidDescriptor,TemperatureDescriptor>::clone() const
{
    return new SmagorinskyBoussinesqThermalProcessor3D<T,FluidDescriptor,TemperatureDescriptor>(*this);
}

*/

}  // namespace plb

#endif  // BOUSSINESQ_THERMAL_PROCESSOR_3D_HH

