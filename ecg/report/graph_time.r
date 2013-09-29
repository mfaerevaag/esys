yv <- c(0.003, 0.452, 0.879, 1.315, 1.756, 2.211, 2.638, 3.069, 3.513, 3.950)
xv <- c(1:10) * 1000000

pdf("graphs/running_time.pdf")

plot(xv, yv, type="p", col = "red", ylab = "time (s)", xlab = "samples")

lines(xv, yv, col = "black")

dev.off()
