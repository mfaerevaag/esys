
data <- read.csv('../output/data.csv', header=T)

time <- as.numeric(data$time) 
raw <- as.numeric(data$raw) 
mwi <- as.numeric(data$mwi)

draw <- function(dat, name, titl, xmin, xmax) {
    pdf(name)

    ylim <- c(min(dat), max(dat))

# draw pulse
    plot(time, dat, type="l", ylim = ylim, col = "red", xlim = c(xmin, xmax), axes = T,  ann = F)

#lines(mwi, col = "red")

    title(titl, xlab = "Time (s)", ylab = "")
    
# add zero-line
    abline(h=0)

    dev.off()
}

mi <- 0
ma <- -4

draw(raw, "graphs/graph_single_qrs.pdf", "QRS kurve", 5.3, 5.9)
draw(raw, "graphs/graph_raw_good.pdf", "Normal puls (raw)", 4 + mi, 12 + ma)
draw(mwi, "graphs/graph_mwi_good.pdf", "Normal puls (mwi)", 4 + mi, 12 + ma)
draw(raw, "graphs/graph_raw_bad.pdf", "Kritisk puls (raw)", 18 + mi, 26 + ma)
draw(mwi, "graphs/graph_mwi_bad.pdf", "Kritisk puls (mwi)", 18 + mi, 26 + ma)
