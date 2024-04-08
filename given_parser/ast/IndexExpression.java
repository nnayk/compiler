package ast;

import java.util.Hashtable;
import java.util.LinkedHashMap;
import java.util.List;

public class IndexExpression
    extends AbstractExpression
{
    private final Expression left;
    private final Expression index;

    public IndexExpression(int lineNum, Expression left, Expression index)
    {
        super(lineNum);
        this.left = left;
        this.index = index;
    }
}
