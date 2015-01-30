// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SampleValidator.h
//! @brief     Defines class SampleValidator
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SAMPLE_VALIDATOR
#define SAMPLE_VALIDATOR

#include <QString>
#include <QModelIndex>

class SampleModel;
class ParameterizedItem;

//! Validates SampleModel for MultiLayerItem suitable for simulation
class SampleValidator
{
public:
    SampleValidator();

    bool isVaildSampleModel(SampleModel *sampleModel);

    QString getValidationMessage() const { return m_validation_message; }

private:
    void iterateSampleModel(SampleModel *sampleModel, const QModelIndex &parentIndex = QModelIndex());

    QString validateMultiLayerItem(ParameterizedItem *item);
    QString validateParticleLayoutItem(ParameterizedItem *item);
    QString validateParticleCoreShellItem(ParameterizedItem *item);

    bool m_valid_sample;
    QString m_validation_message;
};


#endif
