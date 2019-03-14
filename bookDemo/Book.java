package bookDemo;
/**
 * 
 * 图书类
 * @author pi
 *
 */
public class Book {
	private  String name;
	private  String id;//书本在库里的序号//每一个书名对应一个序号
	private String seriesNum;//实际的序列号
	private String num;//内部编号
	private int count;//库存
	static private int bookSumCount=0;//书的总量
	
	
	public Book() {
		super();
		
	}
	public Book(String name, String seriesNum, int count) {
		super();
		bookSumCount++;
		this.id=new Integer(bookSumCount).toString();
		setName(name);
		setSeriesNum(seriesNum);
		setCount(count);
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getId() {
		return id;
	}
	public void setId(String id) {
		this.id = id;
	}
	public int getCount() {
		return count;
	}
	public void setCount(int count) {
		this.count = count;
	}
	public String getSeriesNum() {
		return seriesNum;
	}
	public void setSeriesNum(String seriesNum) {
		this.seriesNum = seriesNum;
	}
	public String getNum() {
		return num;
	}
	public void setNum(String num) {
		this.num = num;
	}
	
}
