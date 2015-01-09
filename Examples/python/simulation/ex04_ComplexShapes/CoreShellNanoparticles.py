"""
Core shell nanoparticles
"""
import numpy
import matplotlib
import pylab
from bornagain import *

phi_min, phi_max = -1.0, 1.0
alpha_min, alpha_max = 0.0, 2.0


def get_sample():
    """
    Build and return the sample representing core shell nano particles
    """
    # defining materials
    m_air = HomogeneousMaterial("Air", 0.0, 0.0 )
    m_shell = HomogeneousMaterial("Shell", 1e-4, 2e-8 )
    m_core = HomogeneousMaterial("Core", 6e-5, 2e-8 )

    # collection of particles
    parallelepiped1_ff = FormFactorBox(16*nanometer, 16*nanometer, 8*nanometer)
    parallelepiped2_ff = FormFactorBox(12*nanometer, 12*nanometer, 7*nanometer)
    shell_particle = Particle(m_shell, parallelepiped1_ff)
    core_particle = Particle(m_core, parallelepiped2_ff)
    core_position = kvector_t(0.0, 0.0, 0.0)

    particle = ParticleCoreShell(shell_particle, core_particle, core_position)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(particle)
    interference = InterferenceFunctionNone()
    particle_layout.addInterferenceFunction(interference)

    air_layer = Layer(m_air)
    air_layer.addLayout(particle_layout)

    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)

    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = Simulation()
    simulation.setDetectorParameters(200, phi_min*degree, phi_max*degree, 200, alpha_min*degree, alpha_max*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    return simulation


def run_simulation():
    """
    Run simulation and plot results
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    result = simulation.getIntensityData().getArray() + 1  # for log scale

    # showing the result
    im = pylab.imshow(numpy.rot90(result, 1), norm=matplotlib.colors.LogNorm(),
                 extent=[phi_min, phi_max, alpha_min, alpha_max], aspect='auto')
    cb = pylab.colorbar(im)
    cb.set_label(r'Intensity (arb. u.)', fontsize=16)
    pylab.xlabel(r'$\phi_f (^{\circ})$', fontsize=16)
    pylab.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
    pylab.show()


if __name__ == '__main__':
    run_simulation()

