package skelton;
/**
 * 分支，包含一个树状结构
 * @author pi
 *
 */
public class Branch {
private String name=null;
private FirstBranch []firstBranches=new FirstBranch[10];

public Branch() {
	// TODO Auto-generated method stub
	this.name=new String("wo");
	for (int i = 0; i < firstBranches.length; i++) {
		this.firstBranches[i]=new FirstBranch();
		firstBranches[i].setName("{ }");
	}
}
public String getName() {
	return name;
}
public void setName(String name) {
	this.name = name;
}
public FirstBranch[] getFirstBranches() {
	return firstBranches;
}
public void setFirstBranches(FirstBranch[] firstBranches) {
	this.firstBranches = firstBranches;
}


}
