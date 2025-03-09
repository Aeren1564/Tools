import os
import shutil
import tarfile
import gzip
import zipfile
import subprocess
import sys

def decompress_file(file_path):
	file_path = os.path.abspath(file_path)
	file_extension = os.path.splitext(file_path)[1]
	output_dir = os.path.dirname(file_path)
	try:
		if file_extension == '.7z':
			subprocess.run(['7z', 'x', file_path, '-o' + output_dir], check=True)
		elif file_extension in ['.tar', '.gz', '.bz2', '.xz']:
			with tarfile.open(file_path) as tar:
				tar.extractall(path=output_dir)
		elif file_extension == '.zip':
			with zipfile.ZipFile(file_path, 'r') as zip_ref:
				zip_ref.extractall(output_dir)
		elif file_extension == '.rar':
			subprocess.run(['unrar', 'x', file_path, output_dir], check=True)
		else:
			print(f"Unsupported file format: {file_extension}")
			return False
		print(f"Decompressed: {file_path} to {output_dir}")
		os.remove(file_path)
		return True
	except Exception as e:
		print(f"Error decompressing {file_path}: {e}")
		return False

def decompress_files(file_list):
	for file in file_list:
		decompress_file(file)

if __name__ == '__main__':
	if len(sys.argv) < 2:
		print("Usage: python decompress.py <file1> <file2> ...")
		sys.exit(1)
	file_list = [os.path.abspath(file) for file in sys.argv[1:]]
	decompress_files(file_list)
