package ast;

public class LvalueIndex
    implements Lvalue
{
    private final int lineNum;
    private final Expression left;
    private final Expression index;

    public LvalueIndex(int lineNum, Expression left, Expression index)
    {
        this.lineNum = lineNum;
        this.left = left;
        this.index = index;
    }
}
