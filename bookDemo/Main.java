package bookDemo;

public class Main {
	
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		//System.out.println(bookMaxStore);+
		Book book1=new Book("天龙八部","654abc",45);
		Book book2=new Book("笑傲江湖","65abc",20);
		Book book3=new Book("神偷帝国","12c",40);
		Book book4=new Book();
		BookBiz bookBiz=new BookBiz();
		bookBiz.addBook(book1);
		System.out.println("ID\t书名\t\t\t库存");
		System.out.println(bookBiz.getInstanceBook()[0].getId()+"\t"+
		bookBiz.getInstanceBook()[0].getName()+"\t\t"+bookBiz.getInstanceBook()[0].getCount());
		/*
		System.out.println(book1.getId()+"\t"+book1.getName()+"\t\t"+book1.getCount());
		System.out.println(book2.getId()+"\t"+book2.getName()+"\t\t"+book2.getCount());
		System.out.println(book3.getId()+"\t"+book3.getName()+"\t\t"+book3.getCount());*/
		bookBiz.bookIn("654abc",20);
		System.out.println(bookBiz.getInstanceBook()[0].getId()+"\t"+
				bookBiz.getInstanceBook()[0].getName()+"\t\t"+bookBiz.getInstanceBook()[0].getCount());
		bookBiz.bookOut("654abc", 30);
		System.out.println(bookBiz.getInstanceBook()[0].getId()+"\t"+
				bookBiz.getInstanceBook()[0].getName()+"\t\t"+bookBiz.getInstanceBook()[0].getCount());
	}
		

}
