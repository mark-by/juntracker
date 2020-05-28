git pull
cd build
cmake --build . --target server -- -j 4
cd ..
mv build/examples/server bin/.
rm -rf bin/templates
rm -rf bin/includes
rm -rf bin/static
cp -r test/templates_test/templatesJuntracker/templates bin/.
cp -r test/templates_test/templatesJuntracker/includes bin/.
cp -r test/templates_test/templatesJuntracker/static bin/.
sudo service supervisor restart
