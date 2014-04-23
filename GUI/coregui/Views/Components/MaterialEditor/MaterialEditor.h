#ifndef MATERIALEDITOR_H
#define MATERIALEDITOR_H


#include <QObject>
#include "MaterialProperty.h"
class MaterialModel;

//! The MaterialEditor is the main class to access materials.
class MaterialEditor : public QObject
{
    Q_OBJECT
public:
    MaterialEditor(MaterialModel *model);
    virtual ~MaterialEditor();

    static MaterialProperty getMaterialProperty(const QString &name);
    static MaterialProperty selectMaterialProperty();
    static MaterialProperty getDefaultMaterialProperty();
private:
    MaterialProperty this_selectMaterialProperty();
    MaterialProperty this_getMaterialProperty(const QString &name);
    MaterialProperty this_getDefaultMaterialProperty();

    static MaterialEditor *m_instance;
    MaterialModel *m_materialModel;
};



#endif


