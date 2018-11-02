package dataStructure.datastructure.spider;

import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.io.IOException;

public class Jsoup {
    public static final String BASE_URL_CSMONITOR = "https://www.csmonitor.com";
    public String FINAL_URL = "";
    public Article article=null;
    public void startSpider() {
        getFinalURL();
        if (FINAL_URL != null) {
            try {
                Document document = org.jsoup.Jsoup.connect(FINAL_URL).get();

//                getFinalStoryImg(document);
                String title=getFinalTitle(document);
                System.out.print(title);
                String author=getFinalAuthor(document);
                String contnet=getFinalContent(document);
                article=new Article(System.currentTimeMillis(),title,author,contnet);
                System.out.print(article.toString());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
    public Article getArticle(){
        return article;
    }

//    private Image getFinalStoryImg(Document doc) {
//
//    }

    private String getFinalTitle(Document doc) {
        return doc.title();
    }

    private String getFinalAuthor(Document doc) {
        Element element=doc.getElementsByClass("staff-name").first();

        return element.text();
    }

    private String getFinalContent(Document doc) {
        StringBuilder stringBuilder=new StringBuilder();
        Element element=doc.getElementsByTag("article").first();
        Elements elements=element.getElementsByClass("story-two").first().children();

        for (Element e:elements
                ) {
            System.out.print(e.tagName());
            if (!e.tagName().equals("div")){
                stringBuilder.append(e.outerHtml()).append("<br><br>");
            }

        }
        return stringBuilder.toString();
    }

    private String getFinalURL() {
        try {
            Document doc = org.jsoup.Jsoup.connect(BASE_URL_CSMONITOR).get();
            Element element = doc.getElementsByClass("ezp-block-content").first().getElementsByClass("story_detail")
                    .first();
            if (element != null) {
                Element element1 = element.getElementsByTag("a").first();
                FINAL_URL = element1.attr("href");
                System.out.println(FINAL_URL);
                Thread.sleep(1000L);
                FINAL_URL = BASE_URL_CSMONITOR + FINAL_URL;
                System.out.println(FINAL_URL);
            } else {
                System.out.print("Final NULL");
                FINAL_URL = null;
            }
        } catch (Exception e) {
            System.out.print("error in getFinalUrl");
            e.printStackTrace();
        }

        return FINAL_URL;
    }
}
