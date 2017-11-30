// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GUIObjectBuilder.h
//! @brief     Defines class GUIObjectBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef GUIOBJECTBUILDER_H
#define GUIOBJECTBUILDER_H

#include "INodeVisitor.h"
#include <QString>
#include <QMap>

class Material;
class InstrumentModel;
class SampleModel;
class SessionItem;
class DocumentModel;
class GISASSimulation;
class ExternalProperty;

//! Class to build SampleModel and InstrumentModel from domain's ISample
class BA_CORE_API_ GUIObjectBuilder : public INodeVisitor
{
public:
    GUIObjectBuilder();
    virtual ~GUIObjectBuilder(){}

    SessionItem* populateSampleModel(SampleModel* sample_model,
                                     const GISASSimulation &simulation,
                                     const QString &sample_name=QString());

    SessionItem* populateSampleModel(SampleModel* sample_model,
                                     const ISample &sample,
                                     const QString &sample_name=QString());

    SessionItem* populateInstrumentModel(InstrumentModel* p_instrument_model,
                                         const GISASSimulation &simulation,
                                               const QString &instrument_name=QString());

    SessionItem* populateDocumentModel(DocumentModel* p_documentModel,
                                       const GISASSimulation &simulation);


    using INodeVisitor::visit;

    void visit(const ParticleLayout *);

    void visit(const Layer*);

    void visit(const MultiLayer*);

    void visit(const Particle*);
    void visit(const ParticleDistribution*);
    void visit(const ParticleCoreShell*);
    void visit(const ParticleComposition*);
    void visit(const MesoCrystal*);
    void visit(const Crystal*);

    void visit(const FormFactorAnisoPyramid*);
    void visit(const FormFactorBox*);
    void visit(const FormFactorCone*);
    void visit(const FormFactorCone6*);
    void visit(const FormFactorCuboctahedron*);
    void visit(const FormFactorCylinder*);
    void visit(const FormFactorDodecahedron*);
    void visit(const FormFactorEllipsoidalCylinder*);
    void visit(const FormFactorFullSphere*);
    void visit(const FormFactorFullSpheroid*);
    void visit(const FormFactorHemiEllipsoid*);
    void visit(const FormFactorIcosahedron*);
    void visit(const FormFactorPrism3*);
    void visit(const FormFactorPrism6*);
    void visit(const FormFactorPyramid*);
    void visit(const FormFactorRipple1*);
    void visit(const FormFactorRipple2*);
    void visit(const FormFactorTetrahedron*);
    void visit(const FormFactorDot*);
    void visit(const FormFactorTruncatedCube*);
    void visit(const FormFactorTruncatedSphere*);
    void visit(const FormFactorTruncatedSpheroid*);

    void visit(const InterferenceFunctionRadialParaCrystal*);
    void visit(const InterferenceFunction2DParaCrystal*);
    void visit(const InterferenceFunction1DLattice*);
    void visit(const InterferenceFunction2DLattice*);

    void visit(const RotationX*);
    void visit(const RotationY*);
    void visit(const RotationZ*);
    void visit(const RotationEuler*);

private:
    void buildAbundanceInfo(SessionItem* particleItem);
    void buildPositionInfo(SessionItem* particleItem, const IParticle* sample);
    ExternalProperty createMaterialFromDomain(const Material*);
    SessionItem* InsertIParticle(const IParticle* p_particle, QString model_type);

    SampleModel* m_sampleModel;

    QMap<int, SessionItem*> m_levelToParentItem;
    QMap<QString, double > m_propertyToValue;
    QMap<QString, bool> m_sample_encountered;
    QMap<SessionItem* , const ISample*> m_itemToSample;
    QString m_topSampleName;
};

#endif // GUIOBJECTBUILDER_H
