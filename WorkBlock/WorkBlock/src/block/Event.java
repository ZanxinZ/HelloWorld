package block;
import skelton.*;
import display.*;
/**
 * 事件类
 * 包含各个事务
 * 继承自branch
 * 实现 显示接口
 * @author pi
 *
 */
public class Event extends Branch implements ShowSkelton{
	
	public Event() {
		// TODO Auto-generated constructor stub
		this.setName(" 事件");
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
