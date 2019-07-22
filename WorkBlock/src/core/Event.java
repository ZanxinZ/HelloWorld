package core;
/**
 * 事件类
 * 包含各个事务
 * @author pi
 *
 */
public class Event {
	private ThingOfEvent []things=new ThingOfEvent[10];//任务数组
	public Event() {
		// TODO Auto-generated constructor stub
		for (int i = 0; i < things.length; i++) {
			things[i]=new ThingOfEvent();
			things[i].setTaskName("默认任务"+(i+1));
		}
	}
	public ThingOfEvent[] getThings() {
		return things;
	}

	public void setThings(ThingOfEvent[] things) {
		this.things = things;
	}
	
}
