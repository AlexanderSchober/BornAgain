#ifndef _LAYERROUGHNESSITEMS_H
#define _LAYERROUGHNESSITEMS_H

#include <QtTest>
#include "LayerRoughness.h"
#include "LayerRoughnessItems.h"
#include "TransformToDomain.h"
#include "TransformFromDomain.h"

class TestLayerRoughnessItems : public QObject {
    Q_OBJECT

private slots:
    void test_LayerRoughnessToDomain();
    void test_LayerRoughnessFromDomain();
};

inline void TestLayerRoughnessItems::test_LayerRoughnessToDomain()
{
    LayerBasicRoughnessItem roughnessItem;
    roughnessItem.setRegisteredProperty(LayerBasicRoughnessItem::P_SIGMA, 10.0);
    roughnessItem.setRegisteredProperty(LayerBasicRoughnessItem::P_HURST, 20.0);
    roughnessItem.setRegisteredProperty(LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH, 30.0);

    LayerRoughness *roughness = TransformToDomain::createLayerRoughness(roughnessItem);
    QCOMPARE(roughness->getSigma(), roughnessItem.getRegisteredProperty(LayerBasicRoughnessItem::P_SIGMA).toDouble());
    QCOMPARE(roughness->getHurstParameter(), roughnessItem.getRegisteredProperty(LayerBasicRoughnessItem::P_HURST).toDouble());
    QCOMPARE(roughness->getLatteralCorrLength(), roughnessItem.getRegisteredProperty(LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH).toDouble());
    delete roughness;

    LayerZeroRoughnessItem zeroRoughnessItem;
    QVERIFY(TransformToDomain::createLayerRoughness(zeroRoughnessItem) == 0);
}

inline void TestLayerRoughnessItems::test_LayerRoughnessFromDomain()
{
    LayerRoughness roughness(10.0, 20.0, 30.0);
    LayerBasicRoughnessItem roughnessItem;
    TransformFromDomain::setItemFromSample(&roughnessItem, &roughness);
    QCOMPARE(roughness.getSigma(), roughnessItem.getRegisteredProperty(LayerBasicRoughnessItem::P_SIGMA).toDouble());
    QCOMPARE(roughness.getHurstParameter(), roughnessItem.getRegisteredProperty(LayerBasicRoughnessItem::P_HURST).toDouble());
    QCOMPARE(roughness.getLatteralCorrLength(), roughnessItem.getRegisteredProperty(LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH).toDouble());
}


#endif

