package block;
import skelton.*;
import display.*;
public class Time extends Branch implements ShowSkelton {
	public Time() {
		// TODO Auto-generated constructor stub
		this.setName("时间");
	}
	/**
	 * 显示内部分支
	 */
	public void shwoBranch() {
		// TODO Auto-generated method stub
		for (int i = 0; i < this.getFirstBranches().length; i++) {
			System.out.print(this.getFirstBranches()[i].getName()+":\t");
			for (int j = 0; j < this.getFirstBranches()[i].getSecondBranches().length; j++) {
				System.out.print(this.getFirstBranches()[i].getSecondBranches()[j].getName()+"\t");
			}
			System.out.println();
		}	
	}
}
