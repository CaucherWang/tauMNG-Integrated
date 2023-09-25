cd build/
make -j

L=500
C=500
R=32
tau=0.01

echo "tau = ${tau}"

cd tests/
# ./test_taumng_search /home/hadoop/wzy/dataset/laion1M/laion1M_base.fvecs_norm \
# /home/hadoop/wzy/dataset/laion1M/laion1M_query.fvecs_norm \
# /home/hadoop/wzy/dataset/laion1M/laion1M_groundtruth.ivecs \
# /home/hadoop/wzy/dataset/laion1M/laion1M_L${L}_R${R}_C${C}_tau${tau}.taumng \
# 180 10 0 0 0

# ./test_taumng_search /home/hadoop/wzy/dataset/webvid1M/webvid1M_base.fvecs \
# /home/hadoop/wzy/dataset/webvid1M/webvid1M_query.fvecs \
# /home/hadoop/wzy/dataset/webvid1M/webvid1M_groundtruth.ivecs \
# /home/hadoop/wzy/dataset/webvid1M/webvid1M_L${L}_R${R}_C${C}_tau${tau}.taumng \
# 300 10 0 0 0

./test_taumng_search /home/hadoop/wzy/dataset/yandex-text2image1M/yandex-text2image1M_base.fvecs \
/home/hadoop/wzy/dataset/yandex-text2image1M/yandex-text2image1M_query.fvecs \
/home/hadoop/wzy/dataset/yandex-text2image1M/yandex-text2image1M_groundtruth.ivecs \
/home/hadoop/wzy/dataset/yandex-text2image1M/yandex-text2image1M_L${L}_R${R}_C${C}_tau${tau}.taumng \
120 10 0 0 0

