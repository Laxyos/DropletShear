compile_submodules:
	cd PostModules && sh compile.sh
	echo "PostModules successfully compiled"

compile_core:
	cd Core && sh compile.sh

clean_out:
	sudo rm -rf Output/*