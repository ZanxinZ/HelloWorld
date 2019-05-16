package skelton;
/**
 * 第一层分支
 * @author pi
 *
 */
public class FirstBranch {
private SecondBranch []secondBranches= new SecondBranch[10];;
private String name=null;

public  FirstBranch() {
	this.name=new String();
	for (int i = 0; i < secondBranches.length; i++) {
		this.secondBranches[i]=new SecondBranch();
		secondBranches[i].setName("[ ]");
	}
}
public SecondBranch[] getSecondBranches() {
	return secondBranches;
}
public void setSecondBranches(SecondBranch[] secondBranches) {
	this.secondBranches = secondBranches;
}
public String getName() {
	return name;
}
public void setName(String name) {
	this.name = name;
} 

}
