cd build/
make -j

L=500
C=500
R=32
tau=0.01

cd tests/

# ./test_taumng_index /home/hadoop/wzy/dataset/laion1M/laion1M_base.fvecs_norm \
# /home/hadoop/wzy/dataset/laion1M/laion1M_norm.efanna \
# ${L} ${R} ${C} 0 ${tau} \
# /home/hadoop/wzy/dataset/laion1M/laion1M_L${L}_R${R}_C${C}_tau${tau}.taumng

./test_taumng_index /home/hadoop/wzy/dataset/laion10M/laion10M_base.fvecs_norm \
/home/hadoop/wzy/dataset/laion1M/laion10M_norm.efanna \
${L} ${R} ${C} 0 ${tau} \
/home/hadoop/wzy/dataset/laion1M/laion10M_L${L}_R${R}_C${C}_tau${tau}.taumng

# ./test_taumng_index /home/hadoop/wzy/dataset/webvid1M/webvid1M_base.fvecs \
# /home/hadoop/wzy/dataset/webvid1M/webvid1M.efanna \
# ${L} ${R} ${C} 0 ${tau} \
# /home/hadoop/wzy/dataset/webvid1M/webvid1M_L${L}_R${R}_C${C}_tau${tau}.taumng

# ./test_taumng_index /home/hadoop/wzy/dataset/yandex-text2image1M/yandex-text2image1M_base.fvecs \
# /home/hadoop/wzy/dataset/yandex-text2image1M/yandex-text2image1M.efanna \
# ${L} ${R} ${C} 0 ${tau} \
# /home/hadoop/wzy/dataset/yandex-text2image1M/yandex-text2image1M_L${L}_R${R}_C${C}_tau${tau}.taumng

# ./test_taumng_index /home/hadoop/wzy/dataset/yandex-text2image10M/yandex-text2image10M_base.fvecs \
# /home/hadoop/wzy/dataset/yandex-text2image10M/yandex-text2image10M.efanna \
# ${L} ${R} ${C} 0 ${tau} \
# /home/hadoop/wzy/dataset/yandex-text2image10M/yandex-text2image10M_L${L}_R${R}_C${C}_tau${tau}.taumng