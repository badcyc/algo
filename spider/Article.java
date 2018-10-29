package dataStructure.spider;

public class Article {
    public String title;
    public String content;
    public String author;
    public Long time;

    public Article() {
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }

    public String getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    public Long getTime() {
        return time;
    }

    public void setTime(Long time) {
        this.time = time;
    }

    public Article(Long time, String title, String author, String content) {
        this.title = title;
        this.content = content;
        this.author = author;
        this.time = time;
    }

    @Override
    public String toString() {
        return "Title:" + title + "\n" + "author" + author + "\n\n" + content;
    }
}
