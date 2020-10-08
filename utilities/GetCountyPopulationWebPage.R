#Gets a table from internet and store as dataframe
#Adapted from https://www.r-bloggers.com/2015/01/using-rvest-to-scrape-an-html-table/

library("rvest")
url <- "https://en.wikipedia.org/wiki/Warren_County,_Iowa"
population <- url %>%
  read_html() %>%
  html_nodes(xpath='//*[@id="mw-content-text"]/div[1]/table[2]') %>%
  html_table()
population <- population[[1]]

population
