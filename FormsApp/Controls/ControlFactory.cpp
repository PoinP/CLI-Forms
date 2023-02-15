#include "ControlFactory.h"

ControlFactory& ControlFactory::getInstance()
{
    static ControlFactory theFactory;
    return theFactory;
}

void ControlFactory::registerCreator(ControlCreator* creator)
{
    m_Creators.pushBack(creator);
}

Control* ControlFactory::createControl(std::istream& iStream) const
{
    String type;
    getLine(iStream, type, ',');

    ControlCreator* creator = findCreator(type);

    if (!creator)
    {
        iStream.ignore(1024, '\n');
        return nullptr;
    }

    return creator->createControl(iStream);
}

ControlCreator* ControlFactory::findCreator(String type) const
{
    for (int i = 0; i < m_Creators.size(); i++)
    {
        if (m_Creators[i]->getType() == type)
            return m_Creators[i];
    }

    return nullptr;
}



ControlCreator::ControlCreator(const String& type)
    : m_Type(type)
{
    ControlFactory::getInstance().registerCreator(this);
}

String ControlCreator::getType() const
{
    return m_Type;
}
