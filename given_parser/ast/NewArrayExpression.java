package ast;

import java.util.Hashtable;
import java.util.LinkedHashMap;
import java.util.List;

public class NewArrayExpression
    extends AbstractExpression
{
    private final String size;

    public NewArrayExpression(int lineNum, String size)
    {
        super(lineNum);
        this.size = size;
    }
}
