import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.File;
import javax.imageio.ImageIO;

public class ChiSquareScan {

    public static void main(String[] args) {
        try {
            String inputPath = "C:\\Users\\user\\Desktop\\1113405010\\images.png";
            String outputPath = "chi_square_output.jpg";

            File inputFile = new File(inputPath);

            if (!inputFile.exists()) {
                System.out.println("找不到 input.jpg，請把圖片放在程式同一個資料夾");
                return;
            }

            BufferedImage img = ImageIO.read(inputFile);

            int w = img.getWidth();
            int h = img.getHeight();

            int[][] gray = new int[w][h];

            // 先轉灰階
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    Color c = new Color(img.getRGB(x, y));
                    int g = (c.getRed() + c.getGreen() + c.getBlue()) / 3;
                    gray[x][y] = g;
                }
            }

            BufferedImage out = new BufferedImage(w, h, BufferedImage.TYPE_BYTE_GRAY);

            int window = 3; // 掃描範圍
            int bins = 16; // 灰階分成16格
            double maxValue = 0;

            double[][] result = new double[w][h];

            // 用 Chi-square distance 掃描圖片
            for (int y = window; y < h - window; y++) {
                for (int x = window; x < w - window; x++) {

                    int[] leftHist = new int[bins];
                    int[] rightHist = new int[bins];

                    // 左邊區域
                    for (int yy = y - window; yy <= y + window; yy++) {
                        for (int xx = x - window; xx < x; xx++) {
                            int bin = gray[xx][yy] / 16;
                            leftHist[bin]++;
                        }
                    }

                    // 右邊區域
                    for (int yy = y - window; yy <= y + window; yy++) {
                        for (int xx = x + 1; xx <= x + window; xx++) {
                            int bin = gray[xx][yy] / 16;
                            rightHist[bin]++;
                        }
                    }

                    double chi = 0;

                    // Chi-square 公式
                    for (int k = 0; k < bins; k++) {
                        double hi = leftHist[k];
                        double hj = rightHist[k];

                        if (hi + hj != 0) {
                            chi += ((hi - hj) * (hi - hj)) / (hi + hj);
                        }
                    }

                    chi = chi * 0.5;

                    result[x][y] = chi;

                    if (chi > maxValue) {
                        maxValue = chi;
                    }
                }
            }

            // 把結果轉成圖片
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {

                    int value = 0;

                    if (maxValue != 0) {
                        value = (int) ((result[x][y] / maxValue) * 255);
                    }

                    if (value > 255) {
                        value = 255;
                    }

                    Color color = new Color(value, value, value);
                    out.setRGB(x, y, color.getRGB());
                }
            }

            ImageIO.write(out, "jpg", new File(outputPath));

            System.out.println("完成！");
            System.out.println("輸出圖片：" + outputPath);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}