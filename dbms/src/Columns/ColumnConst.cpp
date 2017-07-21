#include <IO/Operators.h>
#include <IO/WriteBufferFromString.h>

#include <Columns/ColumnConst.h>
#include <Columns/ColumnNullable.h>
#include <Core/FieldVisitors.h>
#include <Common/typeid_cast.h>


namespace DB
{

bool ColumnConst::isNull() const
{
    const ColumnNullable * column_nullable = typeid_cast<const ColumnNullable *>(data.get());
    return column_nullable && column_nullable->isNullAt(0);
}


String ColumnConst::dump() const
{
    String res;
    WriteBufferFromString out(res);

    {
        out << "ColumnConst, size: " << s << ", nested column: " << data->getName() << ", nested size: " << data->size();
        if (data->size())
            out << ", value: " << applyVisitor(FieldVisitorDump(), (*data)[0]);
    }

    return res;
}

}
